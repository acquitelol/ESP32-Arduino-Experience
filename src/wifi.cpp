#include "common.h"
#include "auth.h"
#include "utilities.h"

void Wifi::setup() 
{
    Serial.println("Setting up Wifi...");

    WiFi.disconnect();
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.mode(WIFI_STA);

    Serial.println("Finished setting up Wifi.");
    PRINT_DIVIDER();
}

void Wifi::hostname() 
{
    Serial.println("Setting hostname...");

    String nodeName = "Sensor-" + WiFi.macAddress();
    nodeName.replace(":", "");
    char charNodeName[20];
    nodeName.toCharArray(charNodeName, 20);
    WiFi.setHostname(charNodeName);

    Serial.printf("Set hostname to %s.\n", charNodeName);
    PRINT_DIVIDER();
}

void Wifi::debug()
{
    Serial.printf(
        "Hostname: %s\nSSID: %s\nIP: %s\nMAC: %s\n", 
        WiFi.getHostname(), 
        WIFI_SSID, 
        WiFi.localIP().toString(), 
        WiFi.macAddress().c_str()
    );

    PRINT_DIVIDER();
}

bool Wifi::connect(int maxAttempts) 
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.printf("Attempting to connect to Wifi at SSID: %s.\n", WIFI_SSID);

    int connectionAttempts = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        connectionAttempts++;
        Serial.println("Checking for Wifi...");

        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);

        if (connectionAttempts >= maxAttempts)
        {
            delay(500);
            return false;
        }
    }

    return true;
}