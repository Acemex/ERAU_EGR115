#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Keypad.h>

const char led_red = A0; // Set up constant values for pin assignments
const char led_yellow = A1;
const char servo = 9;
const char sdpin = 4;
Servo servo1;





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
	
	Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

	
void setup()
	{
	servo1.attach(servo); //Attach the the servo to pin 9.
	servo1.write(90); //Move the servo to neutral for testing
	
	SD.begin(sdpin);

}

void loop()
{
	char instr[4];
	
	int incount = 0;
	while (incount < 3)
	{
		char next = keypad.waitForKey();
		
		instr[incount] = next;


		for (int flash = 0; flash < next; flash++ )
		{
			digitalWrite(led_red, 1);
			delay(100);
			digitalWrite(led_red, 0);

		}
	}

}
