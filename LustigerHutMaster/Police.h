#pragma once
#include <Adafruit_NeoPixel.h>

#define HELMET_SPLIT 25

class Police
{
public:
	Police(Adafruit_NeoPixel* strip);
	void runFlashlight(unsigned long milliseconds);
	void ShutOff();
private:
	Adafruit_NeoPixel* _strip;

	unsigned long _lastMilliSeconds;
	unsigned int _currentInterval;
	int _delay;

	int _pixelCount;
	int _split;
	int _blinkState;

	void police();
	void DefaultPolice();
	void WhiteBlue();
	void WhiteRed();

};

