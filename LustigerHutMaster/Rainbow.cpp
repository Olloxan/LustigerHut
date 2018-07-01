#include "Rainbow.h"

Rainbow::Rainbow(Adafruit_NeoPixel* strip)
{
	_strip = strip;
	_lastMilliSeconds = 0;
	_currentInterval = 0;
	_delay = 20;
}

void Rainbow::runRainbow(unsigned long milliseconds)
{
	_currentInterval = milliseconds - _lastMilliSeconds;
	if (_currentInterval > _delay)
	{
		rainbow();
		_lastMilliSeconds = milliseconds;
	}
}

void Rainbow::rainbow() {
	uint16_t i;
	static uint16_t j = 0;

	j++;
	if (j > 255)
		j = 0;
	for (i = 0; i < _strip->numPixels(); i++) {
		_strip->setPixelColor(i, Wheel((i + j) & 255));
	}
	_strip->show();
}

uint32_t Rainbow::Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return _strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);

	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return _strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return _strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
}