#include <Arduino.h>
#include <cstdlib>
#include <ctime>
#include <functional>

void setState(int led, int state, int time);
int getRandomNumber(int lowest, int highest);
void authenticateWifi();