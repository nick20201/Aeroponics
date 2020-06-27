#include <arduino.h>
#include "FSM.h"
#include "./Interfaces/IState.h"
#include "./Interfaces/IServiceProvider.h"
#include "./States/DisplayState.h"
#include "./States/SystemState.h"
#include "./States/PressureOnState.h"
#include "./States/PressureOffState.h"
#include "./States/OffTimeState.h"
#include "./States/OnTimeState.h"
#include "./States/SolenoidState.h"
#include "./States/MaxPumpOnTimeState.h"
#include "./States/PumpErrorState.h"
#include "./Utilities/Debounce.h"
#include "Constants.h"

using namespace StateMachine;

FSM::FSM(Interfaces::IServiceProvider* serviceProvider)
{
    _okButton    = new Utils::Debounce(OK_BUTTON, DEBOUNCE_TIME);
    _leftButton  = new Utils::Debounce(LEFT_BUTTON, DEBOUNCE_TIME);
    _rightButton = new Utils::Debounce(RIGHT_BUTTON, DEBOUNCE_TIME);
    _upButton    = new Utils::Debounce(UP_BUTTON, DEBOUNCE_TIME);
    _downButton  = new Utils::Debounce(DOWN_BUTTON, DEBOUNCE_TIME);

    _states[DISPLAY_STATE]      = new DisplayState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[SYSTEM_STATE]       = new SystemState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[PRESSURE_ON_STATE]  = new PressureOnState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[PRESSURE_OFF_STATE] = new PressureOffState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[ON_TIME_STATE]      = new OnTimeState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[OFF_TIME_STATE]     = new OffTimeState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[SOLENOID_STATE]     = new SolenoidOverrideState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[MAX_PUMP_STATE]     = new MaxPumpOnTimeState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);
    _states[PUMP_ERROR_STATE]   = new PumpErrorState(this, _okButton, _leftButton, _rightButton, _upButton, _downButton, serviceProvider);


    _currentState = _states[PUMP_ERROR_STATE];
    _currentState->EnterState();
}

void FSM::ChangeState(int stateId)
{
    _currentState->LeaveState();
    _states[stateId]->EnterState();
    _currentState = _states[stateId];
}

void FSM::Loop(unsigned long now)
{
    _currentState->Loop(now);
}