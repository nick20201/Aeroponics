#ifndef __LCDDISPLAY__H__
#define __LCDDISPLAY__H__

#include "./Interfaces/ILcdDisplay.h"

class LiquidCrystal;
class LiquidCrystal_I2C;

namespace Aeroponics
{
    class LcdDisplay : public Interfaces::ILcdDisplay
    {
        //LiquidCrystal* _lcd;
        LiquidCrystal_I2C* _lcd; 
        public:
        LcdDisplay();
        void print(const char * msg);
        void clear();
        void setCursor(int col, int row);
    };
}
#endif  //!__LCDDISPLAY__H__