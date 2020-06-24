#include <arduino.h>
#include "SolenoidState.h"
#include "../Constants.h"

using namespace StateMachine;

SolenoidOverrideState::SolenoidOverrideState(Interfaces::IStateMachine* fsm, 
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
                provider),
                _state(false)
{
    strcpy(_title, " Valve Override");
}

void SolenoidOverrideState::Loop(unsigned long now)
{
    _leftButton->Update();
    _rightButton->Update();
    _okButton->Update();
  
    if (!_dataChange)
        return;

    _lcd->setCursor(0, 1);
    _lcd->print(_state ? "      ON ": "      OFF");
    _dataChange = false;
} 

void SolenoidOverrideState::EnterState()
{
    _leftButton->SetCallback(this);
    _rightButton->SetCallback(this);
    _okButton->SetCallback(this);

    DisplayTitle();
    _dataChange = true;
}

void SolenoidOverrideState::LeaveState()
{
    StateBase::LeaveState();
    _state = false;
    _solenoid->SetState(_state);
}

void SolenoidOverrideState::ButtonPressedCallback(int id)
{
    if (id == OK_BUTTON)
    {
        _state = !_state;
       _dataChange = true;
       _solenoid->SetState(_state);
        return;
    }

    if (id == LEFT_BUTTON)
    {
        _fsm->ChangeState(SYSTEM_STATE);
        return;
    }

    if (id == RIGHT_BUTTON)
    {
        _fsm->ChangeState(PRESSURE_ON_STATE);
        return;
    }    
}
    
