#ifndef __SYSTEMSTATE__H__
#define __SYSTEMSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class SystemState : public StateBase
    {
        public:
        SystemState(Interfaces::IStateMachine* fsm,
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

#endif  //!__SYSTEMSTATE__H__