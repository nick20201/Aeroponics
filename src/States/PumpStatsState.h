#ifndef __PUMPSTATSSTATE__H__
#define __PUMPSTATSSTATE__H__

#include "./StateBase.h" 

namespace StateMachine
{
    class PumpStatsState : public StateBase
    {
        public:
        PumpStatsState(Interfaces::IStateMachine* fsm,
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

#endif  //!__PUMPSTATSSTATE__H__