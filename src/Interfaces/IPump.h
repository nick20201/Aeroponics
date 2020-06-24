#ifndef __IPUMP__H__
#define __IPUMP__H__

namespace Interfaces
{
    class IPump 
    {
        public:
        virtual void Loop(unsigned long now) = 0;
        virtual int GetPressure() = 0;
    };
}

#endif  //!__IPUMP__H__