#include <arduino.h>
#include "Pump.h"
#include "../Constants.h"
#include "../Interfaces/IRepository.h"
#include "../Interfaces/IStateMachine.h"

using namespace Control;

Pump::Pump(Interfaces::IRepository* repo) :
    _repo(repo),
    _switchedOff(false),
    _lowPressureLatch(false),
    _currentState(false),
    _stateMachine(NULL)
{
    pinMode(PUMP_OUTPUT, OUTPUT);
}

int Pump::GetPressure()
{
    //See https://wiki.dfrobot.com/Gravity__Water_Pressure_Sensor_SKU__SEN0257
    float V = analogRead(PRESSURE_SENSOR) * 5.00 / 1024;     //Sensor output voltage
    float P = ((V - PRESSURE_OFFSET) * 400) / DIVISOR_MPA_TO_PSI;             //Calculate water pressure    
    return P;
}

void Pump::CheckOnTime(unsigned long now)
{
    if ((((unsigned long)_repo->GetPumpMaxRunTime() * 1000) + _onTime) < now)
    {
        //opps we have an error, this will require a reset
        _repo->SetSystemState(false);
        SwitchPumpOff();

        if (_stateMachine != NULL)
        {
            _stateMachine->ChangeState(PUMP_ERROR_STATE);            
        }
    }
}

void Pump::Loop(unsigned long now)
{
    bool systemState = _repo->GetSystemState();
    if (!systemState && !_switchedOff)
    {
        digitalWrite(PUMP_OUTPUT, LOW);
        _switchedOff = true;
    }

    if (systemState)
        _switchedOff = false;
    
    if (_switchedOff)
        return;

    int val = GetPressure();

    if (val <= _repo->GetPressureOn())
        _lowPressureLatch = true;

    if (val >= _repo->GetPressureOff())
        _lowPressureLatch = false;        

    if (_lowPressureLatch)
    {
        if (!_currentState)
        {
    	    digitalWrite(PUMP_OUTPUT, HIGH);
            _currentState = true;
            _onTime = now;
        }
        CheckOnTime(now);
    }
    else
    {
        if (_currentState)
        {
            digitalWrite(PUMP_OUTPUT, LOW);
            _currentState = false;
            _onTime = 0;
        }
    }
}

void Pump::SwitchPumpOff()
{
    if (_currentState)
    {
        digitalWrite(PUMP_OUTPUT, LOW);
        _currentState = false;
        _onTime = 0;
        _lowPressureLatch = false;
    } 
}
