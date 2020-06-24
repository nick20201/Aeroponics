#ifndef __STATEBASE__H__
#define __STATEBASE__H__

#include "../Interfaces/IState.h"
#include "../Utilities/Debounce.h"
#include "../Interfaces/IStateMachine.h"
#include "../Interfaces/IServiceProvider.h"
#include "../Interfaces/IRepository.h"
#include "../Interfaces/IStateMachine.h"
#include "../Interfaces/IPump.h"
#include "../Interfaces/ISolenoid.h"
#include "../Interfaces/ILcdDisplay.h"
#include <LiquidCrystal.h>


namespace StateMachine
{
    class StateBase : public Interfaces::IState, public Utils::IButtonPressCallBack
    {
        protected:
            Utils::Debounce* _okButton;
            Utils::Debounce* _leftButton;
            Utils::Debounce* _rightButton;
            Utils::Debounce* _upButton;
            Utils::Debounce* _downButton;
            Interfaces::IStateMachine* _fsm;
            Interfaces::IRepository* _repo;
            Interfaces::IPump* _pump;
            Interfaces::ISolenoid* _solenoid;
            Interfaces::ILcdDisplay* _lcd;

            char _title[16];
            void DisplayTitle();
            void clear();
            unsigned long _lastDisplayTime;
            bool _dataChange;
        public:
        StateBase(Interfaces::IStateMachine* fsm,
            Utils::Debounce* okButton,
            Utils::Debounce* leftButton,
            Utils::Debounce* rightButton,
            Utils::Debounce* upButton,
            Utils::Debounce* downButton,
            Interfaces::IServiceProvider* provider);

            void EnterState();
            void LeaveState();
            void Loop(unsigned long now);    
    };
}


#endif  //!__STATEBASE__H__