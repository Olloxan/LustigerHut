#pragma once
#include <Adafruit_NeoPixel.h>

class CircleDefect
{
public:
	CircleDefect(Adafruit_NeoPixel* circle);
	void runCircleDefect(unsigned long milliseconds);
	void reset();

private:
	Adafruit_NeoPixel* _circle;
	unsigned long _lastEffectMS;
	unsigned long _lastResetMS;
	unsigned long _lastDyingMS;
	unsigned int _effectInterval;
	unsigned int _resetInterval;
	unsigned int _dyingInterval;
	unsigned int _effectDelay;
	unsigned int _resetDelay;
	unsigned int _dyingDelay;
	int _dyingLED;
	int _dyingCounter;
	int _flickerCounter;
	bool _LEDon;
	bool _IsledDying;

	void circleDefect();
	void resetCircle();
	unsigned int rand(int delay);
};
