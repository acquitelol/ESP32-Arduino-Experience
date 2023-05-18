namespace Utilities
{
    extern void authenticateWifi();
    extern uint32_t getAbsoluteHumidity(float temperature, float humidity);
}

namespace Wifi 
{
    extern void setup();
    extern void hostname();
    extern void debug();
    extern bool connect(int maxAttempts = 300);
}
