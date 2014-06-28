#include <Arduino.h>
#include "SteamSensor.h"

/**
 * @file SteamSensor.cpp
 * @author Benoit Cotte
 * @version 1.0
 */


//-----------------------------------------------------//
// CONSTRUCTORS
//-----------------------------------------------------//

/**
 * @brief MoitsureSensors Class Constructors
 */
SteamSensor::SteamSensor(){
	// nothing to do here
}

void SteamSensor::init(uint8_t initDuration, unsigned long maxDuration){
	_steamValue = 0;
	_isNew = false;
	_maxDuration = maxDuration;
	_startTime = millis();
	_stopTime = _startTime;
	uint16_t steamSensorMin = 1023;
	unsigned long initStart = _startTime;
	unsigned long initStop = _startTime;
  	while ((initStop - initStart ) < initDuration) 
  	{
  		led.blink(500);
		initStop = millis();
  		if (steamsensor.isAvailable()) 
      	{
      		steamSensorMin = steamsensor.getValue();	// Determined during calibration
      		// Serial.print("Min is ");
      		// Serial.println(steamSensorMin);
  		}
  	}
  	return steamSensorMin;
}


//-----------------------------------------------------//
// GENERAL
//-----------------------------------------------------//

/**
 * @brief
 */
bool SteamSensor::isAvailable(){
	_stopTime = millis();
	return (_isNew && (_stopTime - _startTime < _maxDuration )) ;
}

/**
 * @brief
 */
void SteamSensor::readValue(){
	if (!self.isAvailable())< {
		self._isNew = true;
		_startTime = _stopTime;
		_steamValue = analogRead(STEAM_SENSOR_PIN)
	}
}

/**
 * @brief
 */
uint8_t SteamSensor::getValue(){
	if (!self.isAvailable())
	{
		self.readValue();
	}
	_isNew = false;
	// to be implemented
	return _steamValue;
}

/**
 * @brief
 */
void SteamSensor::debug(){
	// to be implemented
	Serial.print(F("Steam Value: "));
	Serial.println(_steamValue);
}

