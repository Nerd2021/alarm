#include "pitches.h"
#include "DS3231.h"
#include <Wire.h>
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_keypad

KEYPAD keypad1; //Create instance of this object
DS3231  rtc(SDA, SCL);

const char keyCode[] = {'1', '2', '3', '4'}; // the correct keyCode - change to your own unique set of keys if you like.
char userEntry[] = {0, 0, 0, 0}; // used to store the presses coming in from user
byte userEntryIndex = 0; // used to keep track of where we are in the userEntry, incremented on each press, reset on timeout.
boolean isTime = true;


/************
*Setup stuff*
*************/
void setup() {
  
  //Initialize everything
  rtc.begin(); // Initialize the rtc object
  Serial.begin(9600);
  Serial.println("Qwiic KeyPad Example 6 - KeyCode");

  //Check if keypad is connected
  if (keypad1.begin() == false) {
    Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }

  //Print
  Serial.print("Initialized. Firmware Version: ");
  Serial.println(keypad1.getVersion());
  Serial.println("\n\r\n\rPlease type in the correct 4 digit KeyCode:");
  
}

/********************************************
*Check if the entry matches the correct code*
********************************************/
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

/********************************************
*Repeated constantly*
********************************************/
void loop() {
  
  //printf(rtc.getTimeStr());
  keypad1.updateFIFO();  // necessary for keypad to pull button from stack to readable register
  char button = keypad1.getButton(); //Get the button input
  
  //Check if it's time
  if(isTime){
    tone(6, NOTE_E5, 100);//Play sound for 100 ms
    delay(250); //Wait for 250 ms
    noTone(8); //Stop the tone
  }

  //Check if the keypad has been pressed
  if (button == -1)
  {
    Serial.print("No keypad detected");
    delay(1000);
  }
  else if (button != 0)
  {
    userEntry[userEntryIndex] = button; // store button into next spot in array, note, index is incremented later
    printEntry();
    if (checkEntry() == true)
    {
      Serial.print("\n\r\n\rKeycode correct. Wahooooooooooo!");
      clearEntry();
      delay(1000);
      isTime = false;
    }
    userEntryIndex++;
    if (userEntryIndex == sizeof(keyCode)) userEntryIndex = 0; // reset
  }

  delay(10); //10 is good, more is better, note this effects total timeout time
  
}
