#ifndef _STEAM_SENSOR_H_
#define _STEAM_SENSOR_H_

/**
 * @file SteamSensor.h
 * @author Benoit Cotte
 * @version 1.0
 */

#include <Arduino.h>

/**
 * @class SteamSensors
 */
class SteamSensor {

	public:

		SteamSensor();

		uint8_t init(uint8_t initDuration, unsigned long maxDuration);

		//	SENSORS
		void readValue();
		bool isAvailable();
		uint8_t getValue();
		void debug();

	private:

		//	VARIABLES
		uint8_t _steamValue;
		bool _isNew;
		unsigned long _startTime;
		unsigned long _stopTime;
		unsigned long _maxDuration;
		static const uint8_t STEAM_SENSOR_PIN = 0;
};

#endif
