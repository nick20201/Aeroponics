#ifndef __SERVICEPROVIDER__H__
#define __SERVICEPROVIDER__H__

#include "./Interfaces/IServiceProvider.h"

namespace Aeroponics
{
    class ServiceProvider : public Interfaces::IServiceProvider
    {
        Interfaces::ISolenoid* _solenoid;
        Interfaces::IPump* _pump;
        Interfaces::IRepository* _repo;
        Interfaces::ILcdDisplay* _lcd;

        public:
        ServiceProvider(Interfaces::ISolenoid* solenoid, Interfaces::IPump* pump, Interfaces::IRepository* repo);
        Interfaces::ISolenoid* GetSolenoid() { return _solenoid; };
        Interfaces::IPump* GetPump() { return _pump; };
        Interfaces::IRepository* GetRepository() { return _repo; };   
        Interfaces::ILcdDisplay* GetLcdDisplay() { return _lcd; };     
    };
}
#endif  //!__SERVICEPROVIDER__H__