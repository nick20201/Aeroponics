#ifndef IREPOSITORY_H
#define IREPOSITORY_H

namespace Interfaces
{
    class IRepository
    {
        public:
            virtual int GetPressureOff() = 0;
            virtual void SetPressureOff(int value) = 0;

            virtual int GetPressureOn() = 0;
            virtual void SetPressureOn(int value) = 0;    

            virtual int GetSprayOffTime() = 0;
            virtual void SetSprayOffTime(int value) = 0;

            virtual int GetSprayOnTime() = 0;
            virtual void SetSprayOnTime(int value) = 0;        

            virtual bool GetSystemState() = 0;         
            virtual void SetSystemState(bool state) = 0;
    };
}
#endif