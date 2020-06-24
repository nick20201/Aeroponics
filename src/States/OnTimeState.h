#ifndef __ONTIMESTATE__H__
#define __ONTIMESTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class OnTimeState : public StateBase
    {
        int _sprayOnTime;
        public:
        OnTimeState(Interfaces::IStateMachine* fsm,
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

#endif  //!__ONTIMESTATE__H__