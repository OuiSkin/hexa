#include <Arduino.h>
#include "print.h"

void setup() {
	Serial.begin(115200);
	delay(1000);
	Serial.println(F("1"));
}

void loop() {
	printCounter();
	delay(500);
}
