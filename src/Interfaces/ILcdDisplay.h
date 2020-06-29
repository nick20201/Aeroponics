#ifndef __ILCDDISPLAY__H__
#define __ILCDDISPLAY__H__

namespace Interfaces
{
    class ILcdDisplay
    {
        public:
        virtual void print(const char * msg) = 0;
        virtual void print(unsigned long value) = 0;
        virtual void print(int value) = 0;
        virtual void clear() = 0;
        virtual void setCursor(int col, int row) = 0;
        virtual void backlight(bool state) = 0;
    };
}

#endif  //!__ILCDDISPLAY__H__