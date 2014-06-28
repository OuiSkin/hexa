#ifndef _STEAM_SENSOR_H_
#define _STEAM_SENSOR_H_

/**
 * @file SteamSensor.h
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>
#include "Led.h"

/**
 * @class SteamSensors
 */
class SteamSensor {

	public:

		SteamSensor(unsigned long maxDuration);

		uint8_t initSensor(uint16_t initDuration, Led led);

		//	SENSORS
		void readValue();
		bool isAvailable();
		uint8_t getValue();
		void debug();

	private:

		//	VARIABLES
		uint8_t _steamValue;
		unsigned long _startTime;
		unsigned long _stopTime;
		unsigned long _maxDuration;
        uint16_t _steamSensorMin = 1023;
		static const uint8_t STEAM_SENSOR_PIN = 0;
};

#endif
