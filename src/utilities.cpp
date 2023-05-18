#include "common.h"
#include "utilities.h"
#include "auth.h"

void Utilities::authenticateWifi() 
{   
    PRINT_DIVIDER();
    Wifi::setup();
    Wifi::hostname();
    delay(300);

    if (Wifi::connect())
    {
        Serial.printf("Successfully connected to Wifi with SSID: %s.\n", WiFi.SSID());
    } 
    else
    {
        Serial.println("Failed to connect to Wifi. Retrying...");
        return authenticateWifi();
    }

    delay(300);
    PRINT_DIVIDER();
    Wifi::debug();
}

uint32_t Utilities::getAbsoluteHumidity(float temperature, float humidity) 
{
    const float absoluteHumidity = 216.7f * (
        (humidity / 100.0f) * 6.112f 
            * exp((17.62f * temperature) / (243.12f + temperature)) 
            / (273.15f + temperature)
    );
    
    return static_cast<uint32_t>(1000.0f * absoluteHumidity);
}
