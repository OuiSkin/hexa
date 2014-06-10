/**
 * @file pseudocode.cpp
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>
#include "SteamSensor.h"
#include "Led.h"

Led led = Led(11, 12, 13);
SteamSensor steamsensor;

// PROTOTYPES
void sendAverage();

uint8_t sum;			// declare sum 
uint8_t nbrValue;		// declare n 	
uint8_t zone;			// declare zones
uint8_t average[6]; 	// declare the array


unsigned long startTime;
unsigned long stopTime;

void setup ()	{

	// Init serial
	Serial.begin(115200);

	// Init the sensor
	steamsensor.init();

	// Init variables
	zone = 0;

	for (int i = 0; i < 6; ++i)
	{
		average[0] = 0;
	}
}

void loop ()	{

	// Hexa receives signal
	/*
	*	TO BE IMPLEMENTED
	*/

	// LED lights up
	led.shine(WHITE);

	steamsensor.readValue();

	if (steamsensor.getValue() > 0)
	{	
		startTime = millis();		// When value are > 0 ==> start the timer

		sum = 0;

		nbrValue = 0; 
		
		while(steamsensor.getValue() > 0)		// Place sensor on zone i
		{
			steamsensor.readValue(); 			// Read and add it to sum
			sum += steamsensor.getValue();

			led.blink();						// Blink during measure
			nbrValue += 1;						// Increment the number of measures
			steamsensor.debug();

		}
		
		stopTime = millis();			// When value is back to 0 ==> stop the timer

		if(stopTime - startTime >= 2000)		// If time is over 2 seconds
		{
			average[zone] = sum / nbrValue;		// compute the average
			sendAverage();		// send the average 
		} 
		
	}	


}

void sendAverage()	{
	/*
	*	TO BE IMPLEMENTED
	*/
}
	
		



 

