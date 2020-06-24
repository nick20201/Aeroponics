#include <arduino.h>
#include "StateBase.h"

#define CALL_BUTTON_UPDATE(b)  if (b != NULL) b->Update()

using namespace StateMachine;

StateBase::StateBase(Interfaces::IStateMachine* fsm, 
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider) :
        _leftButton(leftButton),
        _rightButton(rightButton),
        _okButton(okButton),
        _upButton(upButton),
        _downButton(downButton),
        _fsm(fsm),
        _lastDisplayTime(0),
        _dataChange(true)
{
    _repo = provider->GetRepository();
    _pump = provider->GetPump();
    _solenoid = provider->GetSolenoid();
    _lcd = provider->GetLcdDisplay();

    memset(_title, 0, sizeof(_title));
}

void StateBase::DisplayTitle()
{
    _lcd->setCursor(0, 0);
    _lcd->print(_title);   
}

void StateBase::EnterState()
{
    _leftButton->SetCallback(this);
    _rightButton->SetCallback(this);
    _okButton->SetCallback(this);
    _upButton->SetCallback(this);
    _downButton->SetCallback(this); 

    clear();
    DisplayTitle();
    _dataChange = true;
}

void StateBase::Loop(unsigned long now)
{
    CALL_BUTTON_UPDATE(_leftButton);
    CALL_BUTTON_UPDATE(_rightButton);
    CALL_BUTTON_UPDATE(_okButton);
    CALL_BUTTON_UPDATE(_upButton);
    CALL_BUTTON_UPDATE(_downButton);
}

void StateBase::LeaveState()
{
    _leftButton->SetCallback(NULL);
    _rightButton->SetCallback(NULL);
    _okButton->SetCallback(NULL);
    _upButton->SetCallback(NULL);
    _downButton->SetCallback(NULL); 
    clear();
}

void StateBase::clear()
{     
    _lcd->clear();
}