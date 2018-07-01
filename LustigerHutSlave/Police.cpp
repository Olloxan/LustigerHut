#include "Police.h"

Police::Police(Adafruit_NeoPixel* strip)
{
	_strip = strip;
	_pixelCount = (int)(_strip->numPixels());
	_delay = 70;
	_blinkState = 0;
	_split = HELMET_SPLIT;
	_strip->begin();
}

void Police::runFlashlight(unsigned long milliseconds)
{
	_currentInterval = milliseconds - _lastMilliSeconds;
	//Serial.println(_currentInterval);
	if (_currentInterval > _delay)
	{
		police();
		_lastMilliSeconds = milliseconds;
	}

}

void Police::police() {
	//Serial.println(_blinkState);
	if (_blinkState > 7)
		_blinkState = 0;

	if (_blinkState % 2 == 0)
		DefaultPolice();
	else if (_blinkState == 1 || _blinkState == 3)
		WhiteBlue();
	else if (_blinkState == 5 || _blinkState == 7)
		WhiteRed();
	_blinkState++;

}

void Police::DefaultPolice() {
	for (int i = 0; i < _split; i++)
		_strip->setPixelColor(i, _strip->Color(0, 0, 255, 0));

	for (int i = 0; i < (_pixelCount - _split); i++)
		_strip->setPixelColor(i + _split, _strip->Color(255, 0, 0, 0));

	_strip->show();
}

void Police::WhiteBlue() {
	for (int i = 0; i < _pixelCount - _split; i++)
		_strip->setPixelColor(i + _split, _strip->Color(255, 0, 0, 0));

	for (int i = 0; i < (_split); i++)
		_strip->setPixelColor(i, _strip->Color(0, 0, 0, 255));

	_strip->show();
}

void Police::WhiteRed() {
	for (int i = 0; i < _split; i++)
		_strip->setPixelColor(i, _strip->Color(0, 0, 255, 0));

	for (int i = 0; i < (_pixelCount - _split); i++) {
		_strip->setPixelColor(i + _split, _strip->Color(0, 0, 0, 255));
	}
	_strip->show();
}


void Police::ShutOff()
{
	for (int i = 0; i<_pixelCount; i++) {
		_strip->setPixelColor(i, _strip->Color(0, 0, 0, 0));
	}
	_strip->show();
}


