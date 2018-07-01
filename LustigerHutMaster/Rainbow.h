#pragma once
#include <Adafruit_NeoPixel.h>

class Rainbow
{
public:
	Rainbow(Adafruit_NeoPixel* strip);
	void runRainbow(unsigned long milliseconds);



private:
	Adafruit_NeoPixel* _strip;
	unsigned long _lastMilliSeconds;
	unsigned int _currentInterval;
	int _delay;

	void rainbow();
	uint32_t Wheel(byte WheelPos);
};