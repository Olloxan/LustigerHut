#include "Flare.h"

Flare::Flare(Adafruit_NeoPixel* strip)
{
	_strip = strip;
	_lastMilliSeconds = 0;
	_currentInterval = 0;
	_delay = 200;
}

void Flare::runFlare(unsigned long milliseconds)
{
	_currentInterval = milliseconds - _lastMilliSeconds;
	if (_currentInterval > _delay)
	{
		flare();
		_lastMilliSeconds = milliseconds;
	}
}

void Flare::flare() {
	uint16_t i;
	static uint16_t j = 0;
	
	j++;
	if (j > 255)
		j = 0;
	for (i = 0; i < _strip->numPixels(); i++) {		
		_strip->setPixelColor(i, Wheel((j) & 255));
	}
	shutOffLEDs();
	_strip->show();
}

uint32_t Flare::Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;	
	if (WheelPos < 85) {
		return _strip->Color(rand(255 - WheelPos * 3), 0, rand(WheelPos * 3));
		//return _strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return _strip->Color(0, rand(WheelPos * 3),rand(255 - WheelPos * 3));
		//return _strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return _strip->Color(rand(WheelPos * 3), rand(255 - WheelPos * 3), 0);
		//return _strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
}

void Flare::shutOffLEDs()
{
	_strip->setPixelColor(20, _strip->Color(0,0,0));
	_strip->setPixelColor(21, _strip->Color(0, 0, 0));
	_strip->setPixelColor(23, _strip->Color(0, 0, 0));
	_strip->setPixelColor(24, _strip->Color(0, 0, 0));
	_strip->setPixelColor(37, _strip->Color(0, 0, 0));
	_strip->setPixelColor(38, _strip->Color(0, 0, 0));
	_strip->setPixelColor(40, _strip->Color(0, 0, 0));
	_strip->setPixelColor(41, _strip->Color(0, 0, 0));
}

uint8_t Flare::rand(uint8_t color)
{
	int temp = random(-20, 20) + (int)color;
	temp = min(temp, 255);
	temp = max(temp, 0);
	return (uint8_t)temp;
}