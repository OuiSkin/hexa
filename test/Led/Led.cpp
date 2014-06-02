#include <Arduino.h>

#include "Led.h"

Led heart = Led(11, 12, 13);

void setup() {

	Serial.begin(115200);

	delay(500);

	Serial.println("Starting");
}

void printStatus() {
	Serial.print(F("red : "));
	Serial.println(heart.getRgb(0));
	Serial.print(F("green : "));
	Serial.println(heart.getRgb(1));
	Serial.print(F("blue : "));
	Serial.println(heart.getRgb(2));
}

void loop() {

	heart.fade(500, RAND, RAND);
	printStatus();
	heart.fade(500, RAND, RAND);
	printStatus();
	heart.fade(500, RAND, RAND);
	printStatus();
	heart.fade(500, RAND, RAND);
	printStatus();
	heart.fade(500, RAND, RAND);
	printStatus();
	heart.fade(500, RAND, RAND);
	printStatus();

	heart.turnOff();

	delay(1000);
}


