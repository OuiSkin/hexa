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

		void init();

		//	SENSORS
		void readValue();
		uint8_t getValue();
		void debug();

	private:

		//	VARIABLES
		uint8_t _steamValue;
		static const uint8_t STEAM_SENSOR_PIN = 0;
};

#endif
