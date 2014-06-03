#include <Arduino.h>

uint32_t counter;

void printCounter() {
	Serial.println(counter);
	counter = counter + 1;
}
