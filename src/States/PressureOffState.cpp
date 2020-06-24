#include <arduino.h>
#include "PressureOffState.h"
#include "../Constants.h"

using namespace StateMachine;

PressureOffState::PressureOffState(Interfaces::IStateMachine* fsm, 
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
void PressureOffState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if (!_dataChange)
        return;

    char num[16];
    sprintf(num, "Pump Off at %3d", _newPressureOffValue);
    _lcd->setCursor(0, 1);
    _lcd->print(num);   

    _dataChange = false; 
} 

void PressureOffState::EnterState()
{
    StateBase::EnterState();

    _newPressureOffValue = _repo->GetPressureOff();
}

void PressureOffState::ButtonPressedCallback(int id)
{   
    switch (id) 
    {
        case UP_BUTTON:
            _newPressureOffValue++;
            if (_newPressureOffValue > MAX_PUMP_OFF_PRESSURE)
                _newPressureOffValue--;                       
            _dataChange = true; 
        break;
        case DOWN_BUTTON:
            _newPressureOffValue--;
            if (_newPressureOffValue <= _repo->GetPressureOn())
                _newPressureOffValue++;  
            _dataChange = true;                            
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(PRESSURE_ON_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(ON_TIME_STATE);
        break;
        default://OK button
          _repo->SetPressureOff(_newPressureOffValue);
    }             
}