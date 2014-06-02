/*
   DHT11 -- DIGITAL 7
   */
#include <Arduino.h>
#include "TempHumSensor.h"

// Only used for sprintf
#include <stdio.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

// Setup a DHT22 instance
TempHumSensor sensor(DHT22_PIN);

void setup(void)
{
	// start serial port
	Serial.begin(9600);
	Serial.println("DHT22 Library Demo");
}

void loop(void)
{
	DHT22_ERROR_t errorCode;

	// The sensor can only be read from every 1-2s, and requires a minimum
	// 2s warm-up after power-on.
	delay(2000);

	Serial.print("Requesting data...");
	errorCode = sensor.readData();
	switch(errorCode)
	{
		case DHT_ERROR_NONE:
			Serial.print("Got Data ");
			Serial.print(sensor.getTemp());
			Serial.print("C ");
			Serial.print(sensor.getHum());
			Serial.println("%");
			// Alternately, with integer formatting which is clumsier but more compact to store and
			// can be compared reliably for equality:
			//
			char buf[128];
			sprintf(buf, "Integer-only reading: Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
					sensor.getTemp()/10, abs(sensor.getTemp()%10),
					sensor.getHum()/10, sensor.getHum()%10);
			Serial.println(buf);
			break;
		case DHT_ERROR_CHECKSUM:
			Serial.print("check sum error ");
			Serial.print(sensor.getTemp());
			Serial.print("C ");
			Serial.print(sensor.getHum());
			Serial.println("%");
			break;
		case DHT_BUS_HUNG:
			Serial.println("BUS Hung ");
			break;
		case DHT_ERROR_NOT_PRESENT:
			Serial.println("Not Present ");
			break;
		case DHT_ERROR_ACK_TOO_LONG:
			Serial.println("ACK time out ");
			break;
		case DHT_ERROR_SYNC_TIMEOUT:
			Serial.println("Sync Timeout ");
			break;
		case DHT_ERROR_DATA_TIMEOUT:
			Serial.println("Data Timeout ");
			break;
		case DHT_ERROR_TOOQUICK:
			Serial.println("Polled to quick ");
			break;
	}
}
