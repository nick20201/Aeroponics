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
                provider)
{
    strcpy(_title, " Pump Stats");
}

void PumpStatsState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    unsigned long time, occurences;
    _pump->GetStats(time, occurences, now);

    _lcd->setCursor(0, 1);
    _lcd->print("On: ");
    _lcd->print(time);
    _lcd->print("s, ");
    _lcd->print(occurences);
    _lcd->print(" x");
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