/**
 * @file pseudocode.cpp
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SteamSensor.h"
#include "Led.h"

// Constantes
#define INITDURATION (uint16_t)2500
#define REDPIN 12
#define GREENPIN 11
#define BLUEPIN 10

//Object
Led led = Led(REDPIN, GREENPIN, BLUEPIN);
SteamSensor steamsensor(3);
SoftwareSerial blueTooth(9, 8);

// PROTOTYPES
 void sendJson(uint8_t z, uint16_t a);

//Variables
uint16_t steamSensorMin = 1023;        // minimum sensor value before calibration
uint16_t steamSensorMax = 160;           // maximum sensor value before calibration
uint16_t sum;			// declare sum 
uint16_t nbrValue;		// declare n 	
uint8_t zone;			// declare zones
uint16_t average[6]; 	// declare the array
unsigned long startTime;
unsigned long stopTime;
uint8_t sensorValue;


void sendJson()
{
	Serial.print(F("{"));
	Serial.print(F("\"zone\":"));
	Serial.print(zone);
	Serial.print(F(","));
	Serial.print(F("\"average\":"));
	Serial.print(average[zone]);
	Serial.print(F("}"));
}

void sendAverage(){
	// Serial.print("Capture valide : ");
	// Serial.print(stopTime - startTime);
	// Serial.print(", steamSensorMin = ");
	// Serial.print(steamSensorMin);
	// Serial.print(", steamSensorMax = ");
	// Serial.print(steamSensorMax);
	// Serial.print(", sum / nbrValue = ");
	// Serial.print(sum / nbrValue);
	// Serial.print(", sum = ");
	// Serial.print(sum);
	// Serial.print(", nbrVal ");
	// Serial.print(nbrValue);
	// Serial.print(", zone ");
	// Serial.print(zone);
	// Serial.print(", Seuil Min ");
	// Serial.print(steamSensorMin);
	// Serial.print(", average[zone] :");
	// Serial.println(average[zone]);
	// Serial.println(data);
    sendJson();
	blueTooth.println(average[zone]);
}

void setup ()	{

	// Init serial
	Serial.begin(9600);
	blueTooth.begin(9600);
	// Init the sensor
	steamSensorMin = steamsensor.initSensor(INITDURATION, led);
	steamSensorMax += steamSensorMin;
	// Serial.print("Setup Min is ");
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
        	sensorValue = steamsensor.getValue();
        	if (sensorValue > steamSensorMin){
        		// Si la valeur est supérieure au minimum
        		// On affiche en vert
	    		led.colorSwitcher(GREEN);
				led.shine();
	    		delay(20);
	        	if (sensorValue > steamSensorMin + 10) {
	        		// Serial.print("zone : ");
	        		// Serial.print(zone);
	        		// Serial.print(", nbrValue : ");
	        		// Serial.print(nbrValue);
	        		// Serial.print(", sensorValue : ");
	        		// Serial.print(sensorValue);
	        		// Serial.print(", sum : ");
	        		// Serial.println(sum);
	        		sum += sensorValue;
	                nbrValue += 1;						// Increment the number of measures
	                // steamsensor.readValue();		// Updated mesure to enter the loop
	            }else{
	        		// Serial.print("steamSensorMin : ");
	        		// Serial.print(steamSensorMin);
	        		// Serial.println(", exit on bad value + 10");
	            	return;
	            }
        	}else{
//        		Serial.println("Exit on bad value");
        		return;
        		// startTime = stopTime;
        		// sum = 0;
        		// nbrValue = 0;
        	}
            stopTime = millis();			// When value is back to 0 ==> stop the timer
        }
//         // Si la capture a durée suffisament de temps
// 		if(stopTime - startTime >= 2000)		// If time is over 2 seconds
// 		{
//             led.colorSwitcher(BLUE);
//             led.shine();
//             delay(100);
//             average[zone] = map(sum / nbrValue, steamSensorMin, steamSensorMax, 0, 100);	// compute the average
//    //          Serial.print("Capture valide : ");
//    //          Serial.print(stopTime - startTime);
//    //          Serial.print(", sum / nbrValue = ");
//    //          Serial.print(sum / nbrValue);
//    //          Serial.print(", nbrVal ");
//    //          Serial.print(nbrValue);
//    //          Serial.print(", zone ");
//    //          Serial.print(zone);
//    //          Serial.print(", Seuil Min ");
//    //          Serial.print(steamSensorMin);
//    //          Serial.print(", average[zone] :");
//    //          Serial.println(average[zone]);
// 			// json = "[{zone:";
// 			// json += zone;
// 			// json += ",avg:";
// 			// json += average[zone];
// 			// json += "}]";
// 			// Serial.println(json);
//             // Serial.print("Moyenne : ");
//             Serial.println(average[zone]);
//             blueTooth.println(average[zone]);
//             stopTime = 0; 
//             startTime = 0;

// //            Serial.println("10");
// 			// Serial.print("average zone ");
// 			// Serial.print(zone);
// 			// Serial.print(" is ");
// 			// Serial.println(average[zone]);
//             // On blink une seconde et demie 
//             led.blink(1500);
//             zone = (zone + 1) % 6 ;
//         }
    }
	while(stopTime - startTime >= 2000)		// If time is over 2 seconds
	{
		led.colorSwitcher(RED);
		led.shine();
	    average[zone] = map(sum / nbrValue, steamSensorMin, steamSensorMax, 0, 100);	// compute the average
        if (!steamsensor.isAvailable())
        {
            blueTooth.println(average[zone]);
//            sendAverage();
            stopTime = 0;
            startTime = 0;
            led.blink(500);
            zone = (zone + 1) % 6 ;
            return;
        }
	}

}
