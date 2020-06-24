#include <arduino.h>
#include "OffTimeState.h"
#include "../Constants.h"

using namespace StateMachine;

OffTimeState::OffTimeState(Interfaces::IStateMachine* fsm, 
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
    strcpy(_title, " Spray Off Time");
}

void OffTimeState::EnterState()
{
    StateBase::EnterState();

    _sprayOffTime = _repo->GetSprayOffTime();
}

void OffTimeState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if (!_dataChange)
        return;

    char num[16];
    sprintf(num, "%3d seconds", _sprayOffTime);
    _lcd->setCursor(3, 1);
    _lcd->print(num);  

    _dataChange = false;   
} 

void OffTimeState::ButtonPressedCallback(int id)
{
    switch (id) 
    {
        case UP_BUTTON:
            _sprayOffTime += SPRAY_OFF_INC_VALUE;
            if (_sprayOffTime > MAX_SPRAY_OFF)
                _sprayOffTime -= SPRAY_OFF_INC_VALUE;
            _dataChange = true;                 
        break;
        case DOWN_BUTTON:
            _sprayOffTime -= SPRAY_OFF_INC_VALUE;
            if (_sprayOffTime < 0)
                _sprayOffTime += SPRAY_OFF_INC_VALUE;
            _dataChange = true;                 
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(ON_TIME_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(DISPLAY_STATE);
        break;
        default://OK button
          _repo->SetSprayOffTime(_sprayOffTime);
    }        
}