#ifndef __PUMPERRORSTATE__H__
#define __PUMPERRORSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class PumpErrorState : public StateBase
    {
        bool _displayOn;
        unsigned long _laststateChange;
        public:
        PumpErrorState(Interfaces::IStateMachine* fsm,
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider);

            void ButtonPressedCallback(int id);
            void Loop(unsigned long now);
    };
}

#endif  //!__PUMPERRORSTATE__H__