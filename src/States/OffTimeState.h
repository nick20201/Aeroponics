#ifndef __OFFTIMESTATE__H__
#define __OFFTIMESTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class OffTimeState : public StateBase
    {
        int _sprayOffTime;

        public:
        OffTimeState(Interfaces::IStateMachine* fsm,
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


#endif  //!__OFFTIMESTATE__H__