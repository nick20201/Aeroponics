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
    _stateMachine(NULL),
    _totalOnTime(0),
    _startTime(0),
    _onOccurence(0)
{
    pinMode(PUMP_OUTPUT, OUTPUT);
    digitalWrite(PUMP_OUTPUT, HIGH);
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
        SwitchPumpState(false, now);

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
        SwitchPumpState(false, now);
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
    	    SwitchPumpState(true, now);
        }
        CheckOnTime(now);
    }
    else
    {
        if (_currentState)
        {
            SwitchPumpState(false, now);  
        }
    }
}

void Pump::GetStats(unsigned long& time, unsigned long& occurences, unsigned long now)
{
    time = _totalOnTime;
    occurences = _onOccurence;
    if (_currentState)
        time +=  ((now - _startTime) / 1000);
}

void Pump::SwitchPumpState(bool state, unsigned long now)
{
    if (_currentState && !state)
    {
        digitalWrite(PUMP_OUTPUT, HIGH);
        _currentState = false;
        _totalOnTime += (now - _startTime) / 1000;
        _startTime = 0;
        _onTime = 0;
    }

    if (!_currentState && state)
    {
        digitalWrite(PUMP_OUTPUT, LOW);
        _onOccurence++;
        _startTime = now;
        _currentState = true;
        _onTime = now;
    }    
}