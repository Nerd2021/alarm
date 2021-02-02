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

// notes in the melody:
int melody[] = {

  NOTE_C5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G6, 0, NOTE_B5, NOTE_C8
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 2, 4, 4, 4, 2, 2
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(3, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }

  /*
  int i = 0;
  boolean end = true;
  while(true){
    analogWrite(3,i);
    delay(50);
    if(end == true){
      i++;
    }
    else{
      i--;
    }
    if(i==124){
      end = false;
    }
    else if(i==0) {
      end=true;
    }
  }
  */
}
