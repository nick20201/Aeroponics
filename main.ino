#include ".\src\FSM.h"
#include ".\src\Control\Pump.h"
#include ".\src\Control\Solenoid.h"
#include ".\src\Repository.h"
#include ".\src\ServiceProvider.h"

Aeroponics::Repository* repository;
Control::Pump* pump;
Control::Solenoid* solenoid;
Aeroponics::ServiceProvider* provider;
StateMachine::FSM* display;

void setup() 
{
    Serial.begin(115200);   

    repository = new Aeroponics::Repository();
    pump = new Control::Pump(repository);
    solenoid = new Control::Solenoid(repository);
    provider = new Aeroponics::ServiceProvider(solenoid, pump, repository);
    display = new StateMachine::FSM(provider);
}

void loop() 
{       
    unsigned long now = millis();
    display->Loop(now);
    pump->Loop(now);
    solenoid->Loop(now);
}