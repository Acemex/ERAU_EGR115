#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Keypad.h>

const char led_red = A5; // Set up constant values for pin assignments
const char led_yellow = A4;
const char servo = 9;
const char sdpin = 4;
Servo servo1;
File myFile;
//char buf[10];





	//This is the initalization code for the keypad library
	const byte rows = 4; // four rows
	const byte cols = 3; // three columns
	
	char keys[rows][cols] = {
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' },
		{ '*', '0', '#' }
	};

	//byte rowPins[rows] = { 0, 1, 2, 3 }; //connect row pins on board
	//byte colPins[cols] = { 5, 6, 7 }; //connect column pins on board
	byte rowPins[rows] = { 29, 31, 33, 35 }; //MEGA pinout for debug; frees up pins 0 and 1
	byte colPins[cols] = { 39, 41, 43 }; //MEGA pinout for debug; frees up pins 0 and 1
	
	Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

	
void setup()
	{
	//servo1.attach(servo); //Attach the the servo to pin 9.
	//servo1.write(90); //Move the servo to neutral for testing
	
	SD.begin(sdpin);

	Serial.begin(9600);
	Serial.println("Hello, World! Lock program beginning");

}

void loop()
{
	String instr = "0000";
	
	int incount = 0;

	while (incount < 4)
	{
		char next = keypad.waitForKey();
		
		Serial.println(next);

		instr.setCharAt(incount, next);

		Serial.println(instr);
		incount++;
		
	}

	

	if (instr == "1234")
	{
		digitalWrite(led_yellow, HIGH);
		Serial.println("Pattern successful");
		delay(5000);
		digitalWrite(led_yellow, LOW);
	}
	else
	{
		digitalWrite(led_red, HIGH);
		Serial.println("Pattern failed!");
		delay(5000);
		digitalWrite(led_red, LOW);
		
	}



}
