/**
 * @file pseudocode.cpp
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>
#include "SteamSensor.h"
#include "Led.h"

//Object
Led led = Led(10, 11, 12);
SteamSensor steamsensor;

// PROTOTYPES
void sendJson(uint8_t z, uint16_t a);

//Variables
uint16_t steamSensorMin = 1023;        // minimum sensor value before calibration
uint16_t steamSensorMax = 160;           // maximum sensor value before calibration
uint16_t sum;			// declare sum 
uint8_t nbrValue;		// declare n 	
uint8_t zone;			// declare zones
uint16_t average[6]; 	// declare the array
unsigned long startTime;
unsigned long stopTime;

void setup ()	{

	// Init serial
	Serial.begin(115200);

	// Init the sensor
	steamSensorMin = steamsensor.init(2000, 30);

	// Init variables
	zone = 0;

	for (int i = 0; i < 6; ++i)
	{
		average[0] = 0;
	}

 	// // calibrate during the first 2 seconds 
  // 	while (millis() < 2000) 
  // 	{
  // 		led.blink(500);

  // 		steamsensor.readValue();
  //   	// record the maximum sensor value

  //     	steamSensorMax = 160;		// Determined off calibration
  // 		// Serial.print("Max is ");
  // 		// Serial.println(steamSensorMax);

  //   	// record the minimum sensor value
  //   	if (steamsensor.getValue() < steamSensorMin) 
  //     	{
  //     		steamSensorMin = steamsensor.getValue();	// Determined during calibration
  //     		// Serial.print("Min is ");
  //     		// Serial.println(steamSensorMin);
  // 		}
  // 	}


}

void loop ()	{

	// Hexa receives signal
	/*
	*	TO BE IMPLEMENTED
	*/

	// LED lights up
	led.shine(WHITE);

	// steamsensor.readValue();

	// if (steamsensor.getValue() > 0)
	if (steamsensor.isAvailable())
	{	
		startTime = millis();		// When value are > 0 ==> start the timer
		sum = 0;
		nbrValue = 0; 
		// steamsensor.readValue();		// Updated mesure to enter the loop
		// while(steamsensor.getValue() > steamSensorMin)		// Place sensor on zone i
		while(steamsensor.getValue() > steamSensorMin)		// Place sensor on zone i
		{
			// steamsensor.readValue(); 	// Read and add it to sum
			sum += steamsensor.getValue();
			// Serial.print("sum is ");
			// Serial.println(sum);
			led.blink(200);						// Blink during measure
			nbrValue += 1;						// Increment the number of measures
			// steamsensor.readValue();		// Updated mesure to enter the loop
		}
		stopTime = millis();			// When value is back to 0 ==> stop the timer
		// Serial.print("time is ");
		// Serial.println(stopTime - startTime);
		if(stopTime - startTime >= 2000)		// If time is over 2 seconds
		{
			// Serial.print("sum is ");
			// Serial.println(sum);
			// Serial.print("nbrValue is ");
			// Serial.println(nbrValue);				
			average[zone] = map(sum / nbrValue, steamSensorMin, steamSensorMax, 0, 100);	// compute the average
			// json = "[{zone:";
			// json += zone;
			// json += ",avg:";
			// json += average[zone];
			// json += "}]";
			// Serial.println(json);
//			Serial.println(average[zone]);
            Serial.println("10");
			// Serial.print("average zone ");
			// Serial.print(zone);
			// Serial.print(" is ");
			// Serial.println(average[zone]);
			zone = (zone + 1)%6 ;
		} 
	}	
}

void sendJson(uint8_t z, uint16_t a)
{
	Serial.print(F("{"));

		Serial.print(F("\"zone\":"));
		Serial.print(z);
		Serial.print(F(","));

		Serial.print(F("\"average\":"));
		Serial.print(a);

	Serial.print(F("}"));
}
	
		



 

