#ifndef __PUMP__H__
#define __PUMP__H__

#include "../Interfaces/IPump.h"

namespace Interfaces
{
    class IRepository;
}

namespace Control
{    
    class Pump : public Interfaces::IPump
    {
        bool _lowPressureLatch;
        Interfaces::IRepository* _repo;
        bool _switchedOff;
        public:
        Pump(Interfaces::IRepository* repo);
        void Loop(unsigned long now);
        int GetPressure();
    };
}
#endif  //!__PUMP__H__