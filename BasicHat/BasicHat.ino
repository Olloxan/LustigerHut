/*
 Name:		BasicHat.ino
 Created:	7/31/2019 1:10:14 PM
 Author:	ollo
*/

//########################################################
// This is a the setup for a basic hat
//########################################################


#include <Adafruit_NeoPixel.h>
//#include "Rainbow.h"
//#include "Police.h"
#include "Flare.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define STRIP_PIN 6
#define NUM_LEDS_STRIP 16+17+18
#define BRIGHTNESS_STRIP 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_STRIP, STRIP_PIN, NEO_GRBW + NEO_KHZ800);

//Rainbow rainbow(&strip);
Flare flare(&strip);
//Police police(&strip); 

unsigned long currentInterval = 0;
unsigned long lastMilliseconds = 0;


void setup()
{
	Serial.begin(9600);

	// End of trinket special code
	strip.setBrightness(BRIGHTNESS_STRIP);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

	
	
	/* zum Testen der Bluetoothverbindung ohne zusaetzliche hardware */
	pinMode(LED_BUILTIN, OUTPUT);
	lightLED(1000);
}

void loop()
{		
	flare.runFlare(millis());
}

void lightLED(int milliseconds)
{
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(milliseconds);                       // wait for a second
	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW	
	delay(milliseconds);
}
