#ifndef __ISOLENOID__H__
#define __ISOLENOID__H__

namespace Interfaces
{
    class ISolenoid
    {
        public:
        virtual void Loop(unsigned long now) = 0;
        virtual int GetTimeUntilSpray(int& on, int& off) = 0;

        virtual void SetState(bool state) = 0;
        virtual bool GetState() = 0;
    };
}
#endif  //!__ISOLENOID__H__