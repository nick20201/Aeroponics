#include <arduino.h>
#include "PumpStatsState.h"
#include "../Constants.h"

using namespace StateMachine;

PumpStatsState::PumpStatsState(Interfaces::IStateMachine* fsm, 
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
                _displayOn(false),
                _laststateChange(0)
{
    strcpy(_title, " Pump Stats");
}

void PumpStatsState::Loop(unsigned long now)
{
    StateBase::Loop(now);



}

void PumpStatsState::ButtonPressedCallback(int id)
{
    switch (id) 
    {
        case UP_BUTTON:     
            _dataChange = true;  
        break;
        case DOWN_BUTTON:
            _dataChange = true;              
        break;
        case LEFT_BUTTON:
            _fsm->ChangeState(MAX_PUMP_STATE);
        break;
        case RIGHT_BUTTON:
            _fsm->ChangeState(DISPLAY_STATE);
        break;
        default://OK button
        ;
    } 
}