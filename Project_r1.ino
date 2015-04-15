#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Keypad.h>

//const char led_red = A5; // Set up constant values for pin assignments
//const char led_yellow = A4;

const char led_red = 49; //Mega
const char led_yellow = 48; //Mega
const char servo = 8;
const char sdpin = 4;

Servo servo1;

char buf;





	//This is the initalization code for the keypad library
	const byte rows = 4; // four rows
	const byte cols = 3; // three columns
	
	char keys[rows][cols] = {
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' },
		{ '*', '0', '#' }
	};

	//byte rowPins[rows] = { 0, 1, 2, 3 }; //connect row pins on board for Uno
	//byte colPins[cols] = { 5, 6, 7 }; //connect column pins on board for Uno.
	byte rowPins[rows] = { 29, 31, 33, 35 }; //MEGA pinout for debug; frees up pins 0 and 1
	byte colPins[cols] = { 39, 41, 43 }; //MEGA pinout for debug; frees up pins 0 and 1
	
	Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols); //Initalize keypad.

	

	
void setup()
	{
	servo1.attach(servo); //Attach the the servo to pin 9.
	servo1.write(100); //Move the servo to neutral for testing
	
		pinMode(led_red, OUTPUT);
		pinMode(led_yellow, OUTPUT);
		
		Serial.begin(9600);
		
		pinMode(10, OUTPUT);
		digitalWrite(10, HIGH);
		
		if (!SD.begin(sdpin))
		{
			Serial.println("Init failed!");
			
		}
		




	 //datafile = SD.open("passwords.txt");




	
	Serial.println("Hello, World! Lock program beginning");

	//TODO: Add code to unlock door on power cycle here.

}

void loop()
{
	String instr = "0000"; //This will hold the user's entered code.
	
	
	//This handles the user's entry of the code. 
	for (int incount = 0; incount < 4; incount++) //A for loop allows the user to enter 4 digits on the keypad
	{
		char next = keypad.waitForKey(); //Keypad code, accepts input

		digitalWrite(led_yellow, HIGH);
		digitalWrite(led_red, HIGH);
		delay(100);
		digitalWrite(led_yellow, LOW);
		digitalWrite(led_red, LOW);
		
		Serial.println(next); //Debugging code, prints entered data to serial port

		instr.setCharAt(incount, next); //Uses the setCharAt bit of String type to change the number in instr.

		Serial.println(instr); //More debug
		
	}


	Serial.println(SD.exists("password.txt"));
	File datafile = SD.open("password.txt", FILE_READ);
	bool open = 0;
	Serial.println(datafile);
	
	if (datafile)
	{
		Serial.println("File opened");
		
		while (datafile.available()){
			buf = 0;
			Serial.println(buf);

			String lookup = "0000";
			int lookup_index = 0;
			while ((buf != '\n') && (buf != '\r'))
			{
				
				buf = datafile.read();
				
				//buf = buf;
				Serial.println(buf);

				lookup.setCharAt(lookup_index, buf);
				lookup_index++;
				Serial.println(lookup);
				

			}

			if (instr == lookup)
			{	
				digitalWrite(led_yellow, HIGH);
				delay(5000);
				digitalWrite(led_yellow, LOW);
				open = 1;
				break;
			}

		
		}
		datafile.close();
		
		
		if (open == 0)
		{
			digitalWrite(led_red, HIGH);
			delay(5000);
			digitalWrite(led_red, LOW);

		}
	}
	else
	{
		Serial.println("Failed to open file!");
	}
	
	/*
	if (instr == "1234") //If the input is valid, provide feedback to user and unlock door
	{
		digitalWrite(led_yellow, HIGH);
		//Serial.println("Pattern successful"); //Debug, comment out for final submission/demos. Or don't, if a MEGA is used.
		
		servo1.write(170);
		delay(5000);
		digitalWrite(led_yellow, LOW);
		servo1.write(100);
		
		

		//TODO: Add door unlock code.
	}
	else //Notify user they were wrong. 
	{
		digitalWrite(led_red, HIGH);
		//Serial.println("Pattern failed!"); //Same as above.
		delay(5000);
		digitalWrite(led_red, LOW);
		
	}

	*/

}
