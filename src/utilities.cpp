#include "main.h"
#include "utilities.h"
#include "auth.h"

void Pin::setState(int led, int state)
{
    digitalWrite(led, state);
}

void Pin::setState(int led, int state, int time)
{
    setState(led, state);
    delay(time);
}

void Utilities::authenticateWifi() 
{   
    Serial.println("Setting up Wifi...");
    WiFi.disconnect();
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);

    delay(300);

    WiFi.mode(WIFI_STA);
    String nodeName = "Sensor-" + WiFi.macAddress();
    nodeName.replace(":", "");

    char charNodeName[20];
    nodeName.toCharArray(charNodeName, 20);
    WiFi.setHostname(charNodeName);

    delay(300);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.printf("Attempting to connect to Wifi at SSID: %s\n", WIFI_SSID);

    int connectionAttempts = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        connectionAttempts++;
        Serial.println("Checking for Wifi...");

        Pin::setState(LED_PIN, HIGH);
        delay(100);
        Pin::setState(LED_PIN, LOW);

        if (connectionAttempts >= 300)
        {
            delay(500);
            Serial.println("Resetting Wifi...");
            return authenticateWifi();
        }
    }

    Serial.printf(
        "Hostname: %s;\nSSID: %s;\nIP: %s;\nMAC: %s;\n", 
        WiFi.getHostname(), 
        WIFI_SSID, 
        WiFi.localIP().toString(), 
        WiFi.macAddress().c_str()
    );

    Serial.printf("%s\n", DIVIDER);
}

int Utilities::generateRandomNumber(int lowest, int highest) 
{
    std::srand(std::time(nullptr));
    return lowest + (std::rand() % (highest - lowest + 1));
}

uint32_t Utilities::getAbsoluteHumidity(float temperature, float humidity) {
    const float absoluteHumidity = 216.7f * (
        (humidity / 100.0f) * 6.112f 
            * exp((17.62f * temperature) / (243.12f + temperature)) 
            / (273.15f + temperature)
    );
    return static_cast<uint32_t>(1000.0f * absoluteHumidity);
}