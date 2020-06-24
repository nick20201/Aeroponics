#include <arduino.h>
#include "Solenoid.h"
#include "../Constants.h"
#include "../Interfaces/IRepository.h"

using namespace Control;

Solenoid::Solenoid(Interfaces::IRepository* repo) :
    _repo(repo),
    _elapseSinceLastCall(0),
    _elapseTime(0),
    _state(false), 
    _switchedOff(false),
    _timeUntilOn(0),
    _timeUntilOff(0),
    _overrideOn(false)
{
    pinMode(SOLENOID_OUTPUT, OUTPUT);
}

int Solenoid::GetTimeUntilSpray(int& on, int& off)
{
    off = on = -1;
    if (on != _timeUntilOn)
        on = _timeUntilOn / 1000;

    if (off != _timeUntilOff)
        off = _timeUntilOff / 1000;     
}

void Solenoid::SetState(bool state)
{
    _overrideOn = state;
    digitalWrite(SOLENOID_OUTPUT, state ? HIGH : LOW);
}

void Solenoid::Loop(unsigned long now)
{
    bool systemState = _repo->GetSystemState();
    if (!systemState && !_switchedOff)
    {
        digitalWrite(SOLENOID_OUTPUT, LOW);
        _switchedOff = true;
    }

    if (systemState)
        _switchedOff = false;

    unsigned long diff = now - _elapseSinceLastCall;
    _elapseSinceLastCall = now;
    _elapseTime += diff;

    if (!_state)
    {
        unsigned long off = _repo->GetSprayOffTime();
        unsigned long time = off * 1000;
        if (time < _elapseTime)
        {
            _state = true;
            if (!_switchedOff && !_overrideOn)
            {            
                digitalWrite(SOLENOID_OUTPUT, HIGH);
            }
            _elapseTime = 0;            
        }        
        _timeUntilOn = time - _elapseTime;
        _timeUntilOff = -1;
    }
    else
    {
        unsigned long  time = _repo->GetSprayOnTime() * 1000;
        if (time < _elapseTime)
        {
            _state = false;
            if (!_switchedOff && !_overrideOn)
            { 
                digitalWrite(SOLENOID_OUTPUT, LOW);
            }
            _elapseTime = 0;            
        }      
        _timeUntilOff = time - _elapseTime;
        _timeUntilOn = -1;
    }
}