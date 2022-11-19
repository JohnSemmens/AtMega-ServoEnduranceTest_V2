#include "LiquidCrystal_I2C.h"
#include <Wire.h> 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo 
				// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position 

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// https://forum.arduino.cc/t/5v-iic-i2c-twi-lcd-module-adapter-for-arduino-from-ebay/348465/3


// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int RunSwitchPin = 8;
int OptoInterrupter = 7;
// digitalRead(OptoInterrupter)


int centre = 1500;
int right = 1700;
int left = 1300;

long CycleCounter = 0;

void setup()
{
	myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

	// initialize the digital pin as an output.
	pinMode(led, OUTPUT);

	pinMode(RunSwitchPin, INPUT);

	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.clear();
}

void loop()
{
	if (digitalRead(RunSwitchPin))
	{

		digitalWrite(LED_BUILTIN, HIGH);

		// centre
		myservo.write(centre);              // tell servo to go to position in variable 'pos' 
		delay(200);

		// one side 
		myservo.write(right);              // tell servo to go to position in variable 'pos' 
		delay(200);

		// perform optical check; wait on error
		while (digitalRead(OptoInterrupter)); // wait while optical path is clear

		CycleCounter++;
		lcd.setCursor(0, 0);
		lcd.print(CycleCounter);

		digitalWrite(LED_BUILTIN, LOW);

		// centre
		myservo.write(centre);              // tell servo to go to position in variable 'pos' 
		delay(200);

		// The other side 
		myservo.write(left);              // tell servo to go to position in variable 'pos' 
		delay(200);

		// perform optical check;  wait on error
		while (!digitalRead(OptoInterrupter)); // wait while optical path is clear

		

		//myservo.write(1500);              // tell servo to go to position in variable 'pos'
	//	delay(500);

		CycleCounter++;
		lcd.setCursor(0, 0);
		lcd.print(CycleCounter);
	}


}
