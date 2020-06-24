#ifndef __SOLENOIDSTATE__H__
#define __SOLENOIDSTATE__H__

#include "StateBase.h"

namespace StateMachine
{
    class SolenoidOverrideState : public StateBase
    {
        bool _state;
        public:
        SolenoidOverrideState(Interfaces::IStateMachine* fsm,
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider);

        void EnterState();
        void LeaveState();
        void Loop(unsigned long now);    
        void ButtonPressedCallback(int id);
    };
}

#endif  //!__SOLENOIDSTATE__H__