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

void SteamSensor::init(){
	_steamValue = 0;
}


//-----------------------------------------------------//
// GENERAL
//-----------------------------------------------------//

/**
 * @brief
 */
void SteamSensor::readValue(){
	_steamValue = analogRead(STEAM_SENSOR_PIN);
}

/**
 * @brief
 */
uint8_t SteamSensor::getValue(){
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

