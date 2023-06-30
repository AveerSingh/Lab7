/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/aveersingh/Lab7/src/Lab7.ino"
#include "env.h"

#include "blynk.h"
void setup();
void loop();
#line 4 "/Users/aveersingh/Lab7/src/Lab7.ino"
#define TMP36_PIN A0

#include "Blynk.h"
#

void setup()
{
	Serial.begin(9600);
	Blynk.begin(BLYNK_AUTH_TOKEN);
	pinMode(TMP36_PIN, INPUT);
}

void loop()
{
	Blynk.run();
	int reading = analogRead(TMP36_PIN);
	double voltage = (reading * 3.3) / 4095.0;

	// Calculate temperature in Celsius
	double temperatureCelsius = (voltage - 0.5) * 100.0;

	// Calculate temperature in Fahrenheit
	double temperatureFahrenheit = (temperatureCelsius * 9.0 / 5.0) + 32.0;

	// Print temperature
	Serial.print("Temperature: ");
	Serial.print(temperatureCelsius, 2);
	Serial.print(" °C / ");
	Serial.print(temperatureFahrenheit, 2);
	Serial.println(" °F");

	Blynk.virtualWrite(V0, temperatureCelsius);	   // Send temperature in Celsius to Virtual Pin V0
	Blynk.virtualWrite(V2, temperatureFahrenheit); // Send temperature in Fahrenheit to Virtual Pin V2
	Particle.publish("temperature", String(temperatureCelsius));
}

BLYNK_WRITE(V3)
{
	int pushNotification = param.asInt();
	if (pushNotification == 1)
	{
		Blynk.logEvent("push_notifications_", "You did it!");
	}
}
