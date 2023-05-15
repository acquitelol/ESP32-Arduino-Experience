#include <Arduino.h>
#include <functional>
#include "main.h"
#include "utilities.h"

int DELAY = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()
{
  setState(HIGH, DELAY * getRandomNumber(8, 16));
  setState(LOW, DELAY * getRandomNumber(8, 16));
}