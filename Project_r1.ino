#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Keypad.h>

char led_red = A0; // Set up constant values for pin assignments
char led_yellow = A1;
char servo = 9;
char sdpin = 4;
Servo servo1;


void setup()
{


	//This is the initalization code for the keypad library
	const byte rows = 4; // four rows
	const byte cols = 3; // three columns
	
	char keys[rows][cols] = {
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' },
		{ '*', '0', '#' }
	};

	byte rowPins[rows] = { 0, 1, 2, 3 }; //connect row pins on board
	byte colPins[cols] = { 5, 6, 7 }; //connect column pins on board
	

	servo1.attach(servo); //Attach the the servo to pin 9.
	servo1.write(90); //Move the servo to neutral for testing
	
	SD.begin(sdpin);

}

void loop()
{

  /* Do while loop for getting user's input from keypad? */

}
