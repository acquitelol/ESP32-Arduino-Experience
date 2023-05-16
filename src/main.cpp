#include <Arduino.h>
#include <functional>
#include <InfluxDb.h>
#include "WiFi.h"
#include "main.h"
#include "utilities.h"
#include "auth.h"

Influxdb influx(INFLUXDB_HOST);

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()
{
  setState(LED, HIGH, DELAY * getRandomNumber(8, 16));
  setState(LED, LOW, DELAY * getRandomNumber(8, 16));
}