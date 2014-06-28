/**
 * @file pseudocode.cpp
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>
#include "SteamSensor.h"
#include "Led.h"

// Constantes
#define INITDURATION (uint16_t)4000
#define REDPIN 12
#define GREENPIN 11
#define BLUEPIN 10

//Object
 Led led = Led(REDPIN, GREENPIN, BLUEPIN);
 SteamSensor steamsensor(3);

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
	Serial.begin(9600);
	// Init the sensor
	steamSensorMin = steamsensor.initSensor(INITDURATION, led);
	// Serial.print("Min is ");
	// Serial.println(steamSensorMin);

	// Init variables
	zone = 0;

    // Init average data
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
	led.colorSwitcher(WHITE);
	led.shine();
	delay(10);

    // Does SteamSensor has data Availabel
	if (steamsensor.isAvailable())
	{	
        // Init time counter and varaibles
		startTime = millis();		// When value are > 0 ==> start the timer
		stopTime = startTime;		// When value are > 0 ==> start the timer
		sum = 0;
		nbrValue = 0;
        // Getting data for average
//		while(steamsensor.getValue() > steamSensorMin)		// Place sensor on zone i
        // Getting data for 2000 millisecond
        while(stopTime - startTime <= 2000)		// Place sensor on zone i
        {
        	uint8_t sensorValue = steamsensor.getValue();
        	if (sensorValue > 35){    		
	        	if (sensorValue > steamSensorMin) {
	        		sum += sensorValue;
	        		led.colorSwitcher(GREEN);
        			led.shine();
	        		delay(20);
	                nbrValue += 1;						// Increment the number of measures
	                // steamsensor.readValue();		// Updated mesure to enter the loop
	            }else{
	            	delay(250);
	            	return;
	            }
        	}else{
        		startTime = stopTime;
        		sum = 0;
        		nbrValue = 0;
        	}
            stopTime = millis();			// When value is back to 0 ==> stop the timer
        }
		if(stopTime - startTime >= 2000)		// If time is over 2 seconds
		{
            led.colorSwitcher(BLUE);
            led.shine();
            delay(100);
            average[zone] = map(sum / nbrValue, steamSensorMin, steamSensorMax, 0, 100);	// compute the average
            // Serial.print("Capture valide : ");
            // Serial.print(stopTime - startTime);
            // Serial.print(", sum / nbrValue = ");
            // Serial.print(sum / nbrValue);
            // Serial.print(", nbrVal ");
            // Serial.print(nbrValue);
            // Serial.print(", zone ");
            // Serial.print(zone);
            // Serial.print(", Seuil Min ");
            // Serial.print(steamSensorMin);
            // Serial.print(", average[zone] :");
            // Serial.println(average[zone]);
			// json = "[{zone:";
			// json += zone;
			// json += ",avg:";
			// json += average[zone];
			// json += "}]";
			// Serial.println(json);
            // Serial.print("Moyenne : ");
            Serial.println(average[zone]);
//            Serial.println("10");
			// Serial.print("average zone ");
			// Serial.print(zone);
			// Serial.print(" is ");
			// Serial.println(average[zone]);
            led.blink(1500);
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







