#ifndef __ILCDDISPLAY__H__
#define __ILCDDISPLAY__H__

namespace Interfaces
{
    class ILcdDisplay
    {
        public:
        virtual void print(const char * msg) = 0;
        virtual void clear() = 0;
        virtual void setCursor(int col, int row) = 0;
    };
}

#endif  //!__ILCDDISPLAY__H__