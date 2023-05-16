#include <Arduino.h>
#include <functional>
#include "main.h"
#include "utilities.h"

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