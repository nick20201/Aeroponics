#ifndef __PRESSUREOFFSTATE__H__
#define __PRESSUREOFFSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class PressureOffState : public StateBase
    {
        int _newPressureOffValue;
        public:
        PressureOffState(Interfaces::IStateMachine* fsm,
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

#endif  //!__PRESSUREOFFSTATE__H__