#include <arduino.h>
#include <EEPROM.h>
#include "Repository.h"
#include "Constants.h"

using namespace Aeroponics;

Repository::Repository()
{
    int magicNumber = EEPROM.read(MAGIC_NUMBER_ADDR);
    if (magicNumber == MAGIC_NUMBER)
    {
        _pressureOff = EEPROM.read(PRESSURE_OFF_ADDR);
        _pressureOn = EEPROM.read(PRESSURE_ON_ADDR);
        _systemState = (EEPROM.read(SYSTEM_ADDR)) == 1 ? true : false;        
        _sprayOnTime = EEPROM.read(SPRAY_ON_ADDR);
        _sprayOffTime = EEPROM.read(SPRAY_OFF_ADDR_HIGH_BYTE) << 8;
        _sprayOffTime |= EEPROM.read(SPRAY_OFF_ADDR_LOW_BYTE);   
        _maxPumpOnTimeInSeconds = EEPROM.read(MAX_PUMP_ON_ADDR);   
    }
    else
    {
        SetPressureOff(DEFAULT_VALUE_PRESSURE_OFF);
        SetPressureOn(DEFAULT_VALUE_PRESSURE_ON);
        SetSprayOffTime(DEFAULT_VALUE_SPRAY_OFF);
        SetSprayOnTime(DEFAULT_VALUE_SPRAY_ON);
        SetSystemState(DEFAULT_VALUE_SYSTEM_STATE);  
        SetPumpMaxRunTime(DEFAULT_MAX_PUMP_ON_TIME_IN_SECONDS);             
    }
}

void Repository::SetPressureOff(int value) 
{ 
    _pressureOff = value; 
    EEPROM.write(PRESSURE_OFF_ADDR, _pressureOff);
}

void Repository::SetPressureOn(int value) 
{ 
    _pressureOn = value; 
    EEPROM.write(PRESSURE_ON_ADDR, _pressureOn);
}   

void Repository::SetSprayOffTime(int value) 
{
    _sprayOffTime = value;
    EEPROM.write(SPRAY_OFF_ADDR_HIGH_BYTE, _sprayOffTime >> 8);
    EEPROM.write(SPRAY_OFF_ADDR_LOW_BYTE, _sprayOffTime & 0x000000FF);           
}

void Repository::SetSprayOnTime(int value) 
{
    _sprayOnTime = value; 
    EEPROM.write(SPRAY_ON_ADDR, _sprayOnTime); 
} 

void Repository::SetSystemState(bool state) 
{ 
    _systemState = state; 
    EEPROM.write(SYSTEM_ADDR, _systemState ? 1 : 0);    
} 

void Repository::SetPumpMaxRunTime(int maxPumpOnTimeInSeconds) 
{ 
    _maxPumpOnTimeInSeconds = maxPumpOnTimeInSeconds; 
    EEPROM.write(MAX_PUMP_ON_ADDR, _maxPumpOnTimeInSeconds); 
}  