#include "ServiceProvider.h"
#include "LcdDisplay.h"

using namespace Aeroponics;

ServiceProvider::ServiceProvider(Interfaces::ISolenoid* solenoid, Interfaces::IPump* pump, Interfaces::IRepository* repo) :
    _solenoid(solenoid),
    _repo(repo),
    _pump(pump)
{
    _lcd = new LcdDisplay();
    _lcd->clear();
}