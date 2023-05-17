#include "Arduino.h"
#include <iostream>
#include <ctime>

namespace Pin
{
    extern void setState(int pin, int state);
    extern void setState(int pin, int state, int time);
}

namespace Utilities
{
    extern void authenticateWifi();
    extern int generateRandomNumber(int lowest, int highest);
    extern uint32_t getAbsoluteHumidity(float temperature, float humidity);
}