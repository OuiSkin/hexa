#include <Arduino.h>

uint32_t counter;

void setup() {
	Serial.begin(115200);
	delay(1000);
	Serial.println(F("1"));
}

void loop() {
	Serial.println(counter);
	counter = counter + 1;
	delay(500);
}
