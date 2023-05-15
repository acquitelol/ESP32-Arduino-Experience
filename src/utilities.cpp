#include <Arduino.h>
#include <functional>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "utilities.h"

void setState(int STATE, int DELAY)
{
  Serial.printf("%s World! Delay: %d\n", STATE ? "Hello" : "Goodbye", DELAY);
  digitalWrite(LED, STATE);
  delay(DELAY);
}

int getRandomNumber(int lowest, int highest) {
    std::srand(std::time(nullptr));
    return lowest + (std::rand() % (highest - lowest + 1));
}