#ifndef __PRESSUREONSTATE__H__
#define __PRESSUREONSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class PressureOnState : public StateBase
    {
        int _newPressureOnValue;

        public:
        PressureOnState(Interfaces::IStateMachine* fsm,
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

#endif  //!__PRESSUREONSTATE__H__