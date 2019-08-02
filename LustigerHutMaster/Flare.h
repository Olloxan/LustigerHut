#pragma once
#include <Adafruit_NeoPixel.h>

class Flare
{
public:
	Flare(Adafruit_NeoPixel* strip);
	void runFlare(unsigned long milliseconds);



private:
	Adafruit_NeoPixel* _strip;
	unsigned long _lastMilliSeconds;
	unsigned int _currentInterval;
	int _delay;

	void flare();
	uint32_t Wheel(byte WheelPos);	
	uint8_t rand(uint8_t color);
};