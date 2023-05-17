#include "InfluxDb.h"
#include "WiFi.h"
#include "DHT.h"
#include "Adafruit_SGP30.h"

#define DEVICE "ESP32"

#define LED_PIN 2
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define SDA_PIN 21
#define SCL_PIN 22

#define DELAY 30000
#define DIVIDER "-~-~-~-~-~-~-~-~-~-~-~"