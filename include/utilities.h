#include <functional>

void setInput(int PIN);
void setState(int STATE, int DELAY);
void handleButtonPress(int BUTTON, std::function<void()> callback);
int getRandomNumber(int lowest, int highest);