#include <arduino.h>
#include "LcdDisplay.h"
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include "Constants.h"

using namespace Aeroponics;

LcdDisplay::LcdDisplay()
{
    _lcd = new LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.
   //_lcd = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
   //_lcd->begin(16, 2);
    _lcd->init();
    _lcd->backlight();
}

void LcdDisplay::print(const char * msg)
{
    Serial.print(millis());
    Serial.print(" length is ");
    Serial.print(strlen(msg));
    Serial.print(" LCD Print: ");
    Serial.println(msg);
    _lcd->print(msg);
}
void LcdDisplay::clear()
{
    _lcd->clear();
}

void LcdDisplay::setCursor(int col, int row)
{
    _lcd->setCursor(col, row);
}

void LcdDisplay::backlight(bool state)
{
    if (state)
        _lcd->backlight();
    else
        _lcd->noBacklight();  
}