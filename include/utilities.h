#include "Arduino.h"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <string>

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