#ifndef __MAXPUMPONSTATE__H__
#define __MAXPUMPONSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class MaxPumpOnTimeState : public StateBase
    {
        int _maxPumpOnTime;
        public:
        MaxPumpOnTimeState(Interfaces::IStateMachine* fsm,
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider);

        void EnterState();
        void Loop(unsigned long now);    
        void ButtonPressedCallback(int id);
    };
}

#endif  