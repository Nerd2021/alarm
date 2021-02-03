/*

  Melody

  Plays a melody

  circuit:

  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010

  modified 30 Aug 2011

  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone

*/

#include "pitches.h"

#include <Wire.h>
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_keypad
KEYPAD keypad1; //Create instance of this object

const char keyCode[] = {'1', '2', '3', '4'}; // the correct keyCode - change to your own unique set of keys if you like.
char userEntry[] = {0, 0, 0, 0}; // used to store the presses coming in from user
boolean userIsActive = false; // used to know when a user is active and therefore we want to engage timeout stuff

#define TIMEOUT 30 // 100s of milliseconds, used to reset input. 30 equates to 3 second.
byte timeOutCounter = 0; // variable this is incremented to keep track of timeouts.

byte userEntryIndex = 0; // used to keep track of where we are in the userEntry, incremented on each press, reset on timeout.

// notes in the melody:
int melody[] = {

  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C4, NOTE_D5, NOTE_E5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 1
};

boolean a = true;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Qwiic KeyPad Example 6 - KeyCode");

  if (keypad1.begin() == false)   // Note, using begin() like this will use default I2C address, 0x4B.
    // You can pass begin() a different address like so: keypad1.begin(Wire, 0x4A).
  {
    Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }
  Serial.print("Initialized. Firmware Version: ");
  Serial.println(keypad1.getVersion());
  Serial.println("\n\r\n\rPlease type in the correct 4 digit KeyCode:");
  
}

void loop() {
         keypad1.updateFIFO();  // necessary for keypad to pull button from stack to readable register
        char button = keypad1.getButton();
  // put your main code here, to run repeatedly:
  if(a){
        tone(3, NOTE_E5, 100);
      
        delay(250);
      
        // stop the tone playing:
      
        noTone(8);
  }
 
      if (button == -1)
      {
        Serial.print("No keypad detected");
        delay(1000);
      }
      else if (button != 0)
      {
        //Serial.print(button);
        userEntry[userEntryIndex] = button; // store button into next spot in array, note, index is incremented later
        printEntry();
        userIsActive = true; // used to only timeout when user is active
        if (checkEntry() == true)
        {
          Serial.print("\n\r\n\rKeycode correct. Wahooooooooooo!");
          clearEntry();
          userIsActive = false; // don't display timeout stuff.
          delay(1000);
          a = false;
        }
        userEntryIndex++;
        if ( userEntryIndex == sizeof(keyCode)) userEntryIndex = 0; // reset
        timeOutCounter = 0; // reset with any new presses.
      }
    
      delay(10); //10 is good, more is better, note this effects total timeout time
      
    }
    
    // check user entry against keyCode array.
    // if they all match up, then respond with true.
    boolean checkEntry()
    {
    
      for (byte i = 0 ; i < sizeof(keyCode) ; i++)
      {
        if (userEntry[i] == keyCode[i]); // do nothing, cause we're only looking for failures
        else return false;
      }
      return true; // if we get here, all values were correct.
    }
    
    // "clear" entry with all spaces
    void clearEntry()
    {
      for (byte i = 0 ; i < sizeof(userEntry) ; i++)
      {
        userEntry[i] = 0; // fill with spaces
      }
    }
    
    void printEntry()
    {
      Serial.println();
      Serial.print("UserEntry: ");
      for (byte i = 0 ; i < sizeof(userEntry) ; i++)
      {
        Serial.print(char(userEntry[i]));
      }
      Serial.println();
    }
