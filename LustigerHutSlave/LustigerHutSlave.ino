#include <Adafruit_NeoPixel.h>
#include "Rainbow.h"
#include "Police.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 16+17+18
#define BRIGHTNESS 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

Rainbow rainbow(&strip);
Police police(&strip);

const char PING_SYMBOL = '?';
const char RESPONSE_SYMBOL = '!';
const int PING_INTERVAL = 5000;
const int RECONNECT_DETECT_INTERVAL = 5 * PING_INTERVAL;
const int RECONNECT_EFFECT_TIME = 2000;

unsigned long currentInterval = 0;
unsigned long lastMilliseconds = 0;

bool masterHasReconnected = false;

unsigned long masterLastSeen = 0;
unsigned long reconnectEffectStartTime = 0;
bool reconnectEffectEnabled = false;

void setup()
{
	Serial.begin(9600);

	// End of trinket special code
	strip.setBrightness(BRIGHTNESS);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

}

void loop()
{

	if (isPingReceived())
	{
		respondToMaster();		
		if ((millis() - masterLastSeen) > RECONNECT_DETECT_INTERVAL)
			masterHasReconnected = true;
		masterLastSeen = millis();
	}

	

	if (hasReconnectedToMaster())
	{
		enableReconnectEffect();
	}

	if (isReconnectEffectEnabled())
	{
		police.runFlashlight(millis());
	}
	else
	{
		rainbow.runRainbow(millis());
	}

}

bool isPingReceived()
{
	bool returnValue = false;

	while (Serial.available())
		if (Serial.read() == PING_SYMBOL)
			returnValue = true;

	Serial.flush();

	return returnValue;

}

void respondToMaster()
{
	Serial.print(RESPONSE_SYMBOL);
}


bool hasReconnectedToMaster()
{
	bool returnValue = masterHasReconnected;
	masterHasReconnected = false;
	return returnValue;
}

void enableReconnectEffect()
{
	reconnectEffectStartTime = millis();
	reconnectEffectEnabled = true;
}

bool isReconnectEffectEnabled()
{
	if ((millis() - reconnectEffectStartTime) > RECONNECT_EFFECT_TIME)
		reconnectEffectEnabled = false;

	return reconnectEffectEnabled;
}
