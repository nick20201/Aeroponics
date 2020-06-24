#ifndef __ISERVICEPROVIDER__H__
#define __ISERVICEPROVIDER__H__


namespace Interfaces
{
    class ISolenoid;
    class IPump;
    class IRepository;
    class ILcdDisplay;

    class IServiceProvider 
    {
        public:
        virtual ISolenoid* GetSolenoid() = 0;
        virtual IPump* GetPump() = 0;
        virtual IRepository* GetRepository() = 0;
        virtual ILcdDisplay* GetLcdDisplay() = 0;
    };
}
#endif  //!__ISERVICEPROVIDER__H__