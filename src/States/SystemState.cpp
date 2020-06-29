#include <arduino.h>
#include "SystemState.h"
#include "../Constants.h"

using namespace StateMachine;

SystemState::SystemState(Interfaces::IStateMachine* fsm, 
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
    strcpy(_title, "  System State");
}
void SystemState::Loop(unsigned long now)
{
    _leftButton->Update();
    _rightButton->Update();
    _okButton->Update();
  
    if (!_dataChange)
        return;

    _lcd->setCursor(0, 1);
    _lcd->print(_repo->GetSystemState() ? "      ON ": "      OFF");
    _dataChange = false;
} 

void SystemState::EnterState()
{
    _leftButton->SetCallback(this);
    _rightButton->SetCallback(this);
    _okButton->SetCallback(this);

    DisplayTitle();
    _dataChange = true;
}

void SystemState::LeaveState()
{
    StateBase::LeaveState();
}

void SystemState::ButtonPressedCallback(int id)
{
    if (id == OK_BUTTON)
    {
        bool state = _repo->GetSystemState();
        _repo->SetSystemState(!state);
        _dataChange = true;
        return;
    }

    if (id == LEFT_BUTTON)
    {
        _fsm->ChangeState(DISPLAY_STATE);
        return;
    }

    if (id == RIGHT_BUTTON)
    {
        _fsm->ChangeState(SOLENOID_STATE);
        return;
    }    
}