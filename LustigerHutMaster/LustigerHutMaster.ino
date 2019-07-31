#include <Adafruit_NeoPixel.h>
//#include "Rainbow.h"
//#include "Police.h"
#include "CircleDefect.h"
#include "Flare.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define STRIP_PIN 6
#define CIRCLE_PIN 4
#define NUM_LEDS_STRIP 16+17+18
#define NUM_LEDS_CIRCLE 32
#define BRIGHTNESS_STRIP 30
#define BRIGHTNESS_CIRCLE 70
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_STRIP, STRIP_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel circle = Adafruit_NeoPixel(NUM_LEDS_CIRCLE, CIRCLE_PIN, NEO_GRB + NEO_KHZ800);

//Rainbow rainbow(&strip);
Flare flare(&strip);
CircleDefect circleDefect(&circle);
//Police police(&strip); 

const char PING_SYMBOL = '?';
const char RESPONSE_SYMBOL = '!';
const int PING_INTERVAL = 5000;
const int RECONNECT_DETECT_INTERVAL = 5 * PING_INTERVAL;
const int RECONNECT_EFFECT_TIME = 2000;

unsigned long currentInterval = 0;
unsigned long lastMilliseconds = 0;

bool slaveHasReconnected = false;

unsigned long slaveLastSeen = 0;
unsigned long reconnectEffectStartTime = 0;
bool reconnectEffectEnabled = false;

void setup()
{
	Serial.begin(9600);

	// End of trinket special code
	strip.setBrightness(BRIGHTNESS_STRIP);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

	circle.setBrightness(BRIGHTNESS_CIRCLE);
	circle.begin();
	circle.show();
	circleDefect.reset();
	/* zum Testen der Bluetoothverbindung ohne zusaetzliche hardware */
	pinMode(LED_BUILTIN, OUTPUT);
	lightLED(1000);
}

void loop()
{				
	if (isTimeForPing())
	{
		pingSlave();		
	}
	
	if (isResponseReceived())
	{
		lightLED(100);		
		if ((millis() - slaveLastSeen) > RECONNECT_DETECT_INTERVAL)
			slaveHasReconnected = true;
		slaveLastSeen = millis();		
	}

	if (hasSlaveReconnected())
	{
		enableReconnectEffect();
	}

	if (isReconnectEffectEnabled())
	{
		lightLED(1000);
		lightLED(200);
		//police.runFlashlight(millis());				
	}
	else
	{
		flare.runFlare(millis());
		circleDefect.runCircleDefect(millis());
	}
	
}

void lightLED(int milliseconds)
{
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(milliseconds);                       // wait for a second
	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW	
	delay(milliseconds);
}

bool isTimeForPing()
{	
	unsigned long milliseconds = millis();
	currentInterval = milliseconds - lastMilliseconds;
	if (currentInterval > PING_INTERVAL)
	{
		lastMilliseconds = milliseconds;
		return true;
	}	
	return false;
}

void pingSlave()
{
	Serial.print(PING_SYMBOL);
	
}

bool isResponseReceived()
{
	bool returnValue = false;

	while (Serial.available())
		if (Serial.read() == RESPONSE_SYMBOL)
			returnValue = true;

	Serial.flush();

	return returnValue;
}

bool hasSlaveReconnected()
{
	bool returnValue = slaveHasReconnected;
	slaveHasReconnected = false;
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
