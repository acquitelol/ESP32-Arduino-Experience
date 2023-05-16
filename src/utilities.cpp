#include <Arduino.h>
#include <functional>
#include <cstdlib>
#include <ctime>
#include "utilities.h"

void setState(int led, int state, int time)
{
  Serial.printf("%s World! Delay: %d\n", state ? "Hello" : "Goodbye", time);
  digitalWrite(led, state);
  delay(time);
}

int getRandomNumber(int lowest, int highest) {
    std::srand(std::time(nullptr));
    return lowest + (std::rand() % (highest - lowest + 1));
}