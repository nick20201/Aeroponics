#include <arduino.h>
#include "PumpErrorState.h"
#include "../Constants.h"

using namespace StateMachine;

PumpErrorState::PumpErrorState(Interfaces::IStateMachine* fsm, 
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
    strcpy(_title, " PUMP ERROR");
}

void PumpErrorState::Loop(unsigned long now)
{
    StateBase::Loop(now);

    if ((_laststateChange + 1000) > now)
        return;

    _laststateChange = now;
    _displayOn = !_displayOn;
    
    if (_displayOn)
    {
        _lcd->setCursor(0, 0);
        _lcd->print("  PUMP ERROR");
        _lcd->setCursor(0, 1);
        _lcd->print("  OK to clear");
        _lcd->backlight(true);
    }
    else
    {
        _lcd->backlight(false);
    }
}

void PumpErrorState::ButtonPressedCallback(int id)
{
    if (id == OK_BUTTON) 
    {
        _lcd->backlight(true);
        _fsm->ChangeState(SYSTEM_STATE);
    } 
}