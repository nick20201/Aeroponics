#ifndef __PUMP__H__
#define __PUMP__H__

#include "../Interfaces/IPump.h"

namespace Interfaces
{
    class IRepository;
    class IStateMachine;
}

namespace Control
{    
    class Pump : public Interfaces::IPump
    {
        bool _lowPressureLatch;
        Interfaces::IRepository* _repo;
        Interfaces::IStateMachine* _stateMachine;
        bool _switchedOff;
        bool _currentState;
        unsigned long _onTime;

        void CheckOnTime(unsigned long now);
        public:
        Pump(Interfaces::IRepository* repo);
        void Init(Interfaces::IStateMachine* stateMachine) { _stateMachine = stateMachine; }
        void Loop(unsigned long now);
        int GetPressure();
        void SwitchPumpOff();
    };
}
#endif  //!__PUMP__H__