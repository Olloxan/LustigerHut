#include "CircleDefect.h"

CircleDefect::CircleDefect(Adafruit_NeoPixel* circle)
{
	_circle = circle;
	_lastEffectMS = 0;
	_lastResetMS = 0;
	_lastDyingMS = 0;
	_effectInterval = 0;
	_resetInterval = 0;
	_dyingInterval = 0;
	_effectDelay = 150;
	_resetDelay = 60000;
	_dyingDelay = 3000;
	_LEDon = false;
	_IsledDying = false;
	_dyingCounter = 0;
	_dyingLED = random(35);
	_flickerCounter = random(10);	
}

void CircleDefect::runCircleDefect(unsigned long milliseconds)
{
	// led is flickering and dying		
	if (_IsledDying)
	{
		_effectInterval = milliseconds - _lastEffectMS;
		if (_effectInterval > (unsigned int)rand(_effectDelay))
		{
			circleDefect();
			_lastEffectMS = milliseconds;
			_dyingCounter++;
		}

		if (_dyingCounter > _flickerCounter)
		{
			_IsledDying = false;
			_dyingCounter = 0;
			_dyingLED = random(0, 35);
			int infcounter = 0;
			while (_circle->getPixelColor(_dyingLED) == 0)
			{
				if (infcounter > 20)				
					break;				
				_dyingLED = random(0, 35);
				infcounter++;
			}
			_flickerCounter = random(10);
		}
	}
	// should another led die?
	_dyingInterval = milliseconds - _lastDyingMS;
	if (_dyingInterval > _dyingDelay)
	{
		_IsledDying = true;
		_lastDyingMS = milliseconds;
	}

	_resetInterval = milliseconds - _lastResetMS;
	if (_resetInterval > _resetDelay)
	{
		resetCircle();
		_lastResetMS = milliseconds;
		_lastDyingMS = milliseconds;
		_IsledDying = false;
		_dyingLED = random(35);
		_flickerCounter = random(10);
	}
}

void CircleDefect::reset()
{
	resetCircle();
}

void CircleDefect::circleDefect()
{	
	if (_LEDon)
	{
		_circle->setPixelColor(_dyingLED, _circle->Color(255, 0, 0));
		_LEDon = false;
	}
	else
	{
		_circle->setPixelColor(_dyingLED, _circle->Color(0, 0, 0));
		_LEDon = true;
	}
	_circle->show();
}

void CircleDefect::resetCircle()
{
	for (uint8_t i = 0; i < _circle->numPixels(); i++) {
		_circle->setPixelColor(i, _circle->Color(255, 0, 0));
	}
	_circle->show();
}

unsigned int CircleDefect::rand(int delay)
{
	int temp = delay + random(-50, 0);	
	return (unsigned int)temp;
}