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
SteamSensor::SteamSensor(unsigned long maxDuration){
	_steamValue = 0;
	_maxDuration = maxDuration;
	_startTime = millis();
	_stopTime = _startTime;
    _steamSensorMin = 1023;
}

uint8_t SteamSensor::initSensor(uint16_t initDuration, Led led){
	// uint8_t readValue = SteamSensor::getValue();
  uint8_t readValue = SteamSensor::getValue();
  unsigned long initStart = millis();
  unsigned long initStop = initStart;
  uint8_t redValue = 0;
  uint8_t greenValue = 0;
  uint8_t blueValue = 0;
  led.setRgb(redValue, greenValue, blueValue);
  led.shine();
  while ((initStop - initStart ) < initDuration)
  {
    led.setRgb(redValue, greenValue, blueValue);
    led.shine();
    delay(10);
    greenValue+=5;
    redValue+=5;
    blueValue+=5;
    // led.blink(450);
    initStop = millis();
    readValue = SteamSensor::getValue();
    if (_steamSensorMin > readValue)
    {
  		_steamSensorMin = readValue;	// Determined during calibration
    }
  }
  led.colorSwitcher(GREEN);
  led.shine();
  delay(400);
return _steamSensorMin;
}


//-----------------------------------------------------//
// GENERAL
//-----------------------------------------------------//

/**
 * @brief
 */
bool SteamSensor::isAvailable(){
    return SteamSensor::getValue() > _steamSensorMin;
}

/**
 * @brief
 */
//void SteamSensor::readValue(){
//	if (!SteamSensor::isAvailable()){
//		_isNew = true;
//		_startTime = _stopTime;
//		_steamValue = analogRead(STEAM_SENSOR_PIN);
//        Serial.print("Capturing :");
//        Serial.println(_steamValue);
//	}
//}

/**
 * @brief
 */
uint8_t SteamSensor::getValue(){
    _steamValue = analogRead(STEAM_SENSOR_PIN);
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

