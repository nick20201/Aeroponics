#include <arduino.h>
#include "OnTimeState.h"
#include "../Constants.h"

using namespace StateMachine;

OnTimeState::OnTimeState(Interfaces::IStateMachine* fsm, 
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
    strcpy(_title, " Spray On Time");
}

void OnTimeState::EnterState()
{
    StateBase::EnterState();

    _sprayOnTime = _repo->GetSprayOnTime();
}

void OnTimeState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if (!_dataChange)
        return;
    char num[16];
    sprintf(num, "   %3d seconds  ", _sprayOnTime);
    _lcd->setCursor(0, 1);
    _lcd->print(num);     

    _dataChange = false; 
} 

void OnTimeState::ButtonPressedCallback(int id)
{
    switch (id) 
    {
        case UP_BUTTON:
            _sprayOnTime += SPRAY_ON_INC_VALUE;
            if (_sprayOnTime > MAX_SPRAY_ON)
                _sprayOnTime -= SPRAY_ON_INC_VALUE;
            _dataChange = true; 
        break;
        case DOWN_BUTTON:
            _sprayOnTime -= SPRAY_ON_INC_VALUE;
            if (_sprayOnTime < 0)
                _sprayOnTime += SPRAY_ON_INC_VALUE;
            _dataChange = true; 
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(PRESSURE_OFF_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(OFF_TIME_STATE);
        break;
        default://OK button
          _repo->SetSprayOnTime(_sprayOnTime);
    }         
}