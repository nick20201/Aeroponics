#ifndef __SOLENOID__H__
#define __SOLENOID__H__


#include "../Interfaces/ISolenoid.h"

namespace Interfaces
{
    class IRepository;
}

namespace Control
{
    class Solenoid : public Interfaces::ISolenoid
    {
        bool _overrideOn;
        unsigned long  _elapseSinceLastCall;
        unsigned long  _elapseTime;
        bool _state;
        long _timeUntilOn;
        long _timeUntilOff;
        Interfaces::IRepository* _repo;
        bool _switchedOff;

        public:
        Solenoid(Interfaces::IRepository* repo);
        void Loop(unsigned long now);
        int GetTimeUntilSpray(int& on, int& off);

        void SetState(bool state);
        bool GetState() { return _overrideOn || _state; };
    };
}
#endif  //!__SOLENOID__H__