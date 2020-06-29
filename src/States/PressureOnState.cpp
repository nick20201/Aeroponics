#include <arduino.h>
#include "PressureOnState.h"
#include "../Constants.h"

using namespace StateMachine;

PressureOnState::PressureOnState(Interfaces::IStateMachine* fsm, 
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider) : StateBase(fsm, 
                okButton,
                leftButton,
                rightButton,
                upButton,
                downButton,
                provider)
{
    strcpy(_title, "  Pump Pressure");
}

void PressureOnState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if (!_dataChange)
        return;
        
    char num[16];
    sprintf(num, "Pump On at %3d", _newPressureOnValue);
    _lcd->setCursor(0, 1);
    _lcd->print(num);

    _dataChange = false;  
} 

void PressureOnState::EnterState()
{
    StateBase::EnterState();

    _newPressureOnValue = _repo->GetPressureOn();
}

void PressureOnState::ButtonPressedCallback(int id)
{
    switch (id) 
    {
        case UP_BUTTON:
            _newPressureOnValue++;
            if (_newPressureOnValue >= _repo->GetPressureOff())
                _newPressureOnValue--;        
            _dataChange = true;  
        break;
        case DOWN_BUTTON:
            _newPressureOnValue--;
            if (_newPressureOnValue < MIN_PUMP_ON_PRESSURE)
                _newPressureOnValue++;  
            _dataChange = true;              
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(SYSTEM_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(PRESSURE_OFF_STATE);
        break;
        default://OK button
          _repo->SetPressureOn(_newPressureOnValue);
    }   
}