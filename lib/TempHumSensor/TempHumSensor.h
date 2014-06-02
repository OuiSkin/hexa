#ifndef _TEMPERATURE_HUMIDITY_SENSOR_H_
#define _TEMPERATURE_HUMIDITY_SENSOR_H_

// #include <inttypes.h>

// DHT22 is the technical name of the sensor, so we keep it that way
#define DHT22_ERROR_VALUE -995

typedef enum {
	DHT_ERROR_NONE = 0,
	DHT_BUS_HUNG,
	DHT_ERROR_NOT_PRESENT,
	DHT_ERROR_ACK_TOO_LONG,
	DHT_ERROR_SYNC_TIMEOUT,
	DHT_ERROR_DATA_TIMEOUT,
	DHT_ERROR_CHECKSUM,
	DHT_ERROR_TOOQUICK
} DHT22_ERROR_t;

class TempHumiditySensor {

	public:

		TempHumiditySensor(uint8_t pin);

		DHT22_ERROR_t readData();

		int16_t getHum();
		int16_t getTemp();
		void clockReset();

	private:

		uint8_t _bitmask;
		volatile uint8_t *_baseReg;

		uint32_t _lastReadTime;
		int16_t _lastHumidity;
		int16_t _lastTemperature;

};

// Report the humidity in .1 percent increments, such that 635 means 63.5% relative humidity
//
// Converts from the internal integer format on demand, so you might want
// to cache the result.
int16_t TempHumiditySensor::getHum() {
	return _lastHumidity;
}

// Get the temperature in decidegrees C, such that 326 means 32.6 degrees C.
// The temperature may be negative, so be careful when handling the fractional part.
int16_t TempHumiditySensor::getTemp() {
	return _lastTemperature;
}

#endif /*_TEMPERATURE_HUMIDITY_SENSOR_H_*/
