#ifndef __REPOSITORY__H__
#define __REPOSITORY__H__
#include "./Interfaces/IRepository.h"

namespace Aeroponics
{
    class Repository : public Interfaces::IRepository
    {
         int _pressureOff;
        int _pressureOn;
        int _sprayOffTime;
        int _sprayOnTime;
        bool _systemState;
        int _maxPumpOnTimeInSeconds;

        public:
        Repository();

        int GetPressureOff() { return _pressureOff; }
        void SetPressureOff(int value);

        int GetPressureOn() {  return _pressureOn; }
        void SetPressureOn(int value);   

        int GetSprayOffTime() { return _sprayOffTime; } 
        void SetSprayOffTime(int value);

        int GetSprayOnTime() { return _sprayOnTime; }
        void SetSprayOnTime(int value);  

        bool GetSystemState() { return _systemState; }
        void SetSystemState(bool state);

        int GetPumpMaxRunTime() { return _maxPumpOnTimeInSeconds; };         
        void SetPumpMaxRunTime(int maxPumpOnTimeInSeconds);    
    };
}
#endif  //!__REPOSITORY__H__