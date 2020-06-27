#include <arduino.h>
#include "MaxPumpOnTimeState.h"
#include "../Constants.h"

using namespace StateMachine;

MaxPumpOnTimeState::MaxPumpOnTimeState(Interfaces::IStateMachine* fsm, 
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
    strcpy(_title, " Max Pump Time");
}

void MaxPumpOnTimeState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if (!_dataChange)
        return;
    char num[16];
    sprintf(num, "   %3d seconds  ", _maxPumpOnTime);
    _lcd->setCursor(0, 1);
    _lcd->print(num);     

    _dataChange = false;
} 

void MaxPumpOnTimeState::EnterState()
{
    StateBase::EnterState();

    _maxPumpOnTime = _repo->GetPumpMaxRunTime();
}

void MaxPumpOnTimeState::ButtonPressedCallback(int id)
{
    switch (id) 
    {
        case UP_BUTTON:
            _maxPumpOnTime++;
            _dataChange = true;                 
        break;
        case DOWN_BUTTON:
            _maxPumpOnTime--;
            _dataChange = true;                 
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(OFF_TIME_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(DISPLAY_STATE);
        break;
        default://OK button
          _repo->SetPumpMaxRunTime(_maxPumpOnTime);
    } 
}