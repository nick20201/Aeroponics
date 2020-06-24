#include <arduino.h>
#include "Pump.h"
#include "../Constants.h"
#include "../Interfaces/IRepository.h"

using namespace Control;

Pump::Pump(Interfaces::IRepository* repo) :
    _repo(repo),
    _switchedOff(false),
    _lowPressureLatch(false)
{
    pinMode(PUMP_OUTPUT, OUTPUT);
}

int Pump::GetPressure()
{
    // Sensor read 0-231 psi 0.5v - 4.5v
    // 0 - 1024 on analog gives a range of 102 - 921 (0.5 - 4.5v) which maps to 0 - 231 psi 
    int value = analogRead(PRESSURE_SENSOR);
    return (value - PRESSURE_BASE) / PRESSURE_CONVERSION_FACTOR;
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
    	digitalWrite(PUMP_OUTPUT, HIGH);
    else
        digitalWrite(PUMP_OUTPUT, LOW);
}