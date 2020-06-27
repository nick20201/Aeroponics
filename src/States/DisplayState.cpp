#include <arduino.h>
#include "DisplayState.h"
#include "../Constants.h"

using namespace StateMachine;

const char Line1[]    = "Pressure %3d psi";
const char Line2On[]  = "Spray in %3d ";
const char Line2Off[] = "Spray off %3d";

DisplayState::DisplayState(Interfaces::IStateMachine* fsm, 
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
}

void DisplayState::Loop(unsigned long now)
{
    _leftButton->Update();
    _rightButton->Update();

    if ((_lastDisplayTime + DISPLAY_UPDATE_EVERY_X_MILLI) > now)
        return;

    char line[16];
    int onTime;
    int offTime; 
    _solenoid->GetTimeUntilSpray(onTime, offTime);  
    int x = offTime;
    sprintf(line, Line1, _pump->GetPressure());
    _lcd->setCursor(0, 0);
    _lcd->print(line);    
    _lcd->setCursor(0, 1);       

    if (onTime > -1)
        sprintf(line, Line2On, onTime);
    else
        sprintf(line, Line2Off, x);    
    _lcd->print(line);
    _lastDisplayTime = now;   
} 

void DisplayState::EnterState()
{
    _leftButton->SetCallback(this);
    _rightButton->SetCallback(this);

    _lastDisplayTime = millis() - DISPLAY_UPDATE_EVERY_X_MILLI;
}

void DisplayState::ButtonPressedCallback(int id)
{
    if (id == LEFT_BUTTON)
    {
        _fsm->ChangeState(OFF_TIME_STATE);Serial.println("LEFT_BUTTON Button pressed");
        return;
    }

    if (id == RIGHT_BUTTON)
    {
        _fsm->ChangeState(SYSTEM_STATE);Serial.println("RIGHT_BUTTON Button pressed");
        return;
    }
}