#include "InfluxDb.h"
#include "DHT.h"
#include "Adafruit_SGP30.h"
#include "strict_variant/variant.hpp"
#include "Arduino.h"
#include "WiFi.h"
#include <iostream>

#define LED_PIN 2
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define SDA_PIN 21
#define SCL_PIN 22

#define MODULE "ESP32"
#define TEMP_SENSOR "DHT22"
#define CO2_SENSOR "SGP30"
#define DELAY 30000
#define DIVIDER "-~-~-~-~-~-~-~-~-~-~-~"
#define PRINT_DIVIDER() Serial.printf("%s\n", DIVIDER)
