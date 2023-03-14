/* This is for ECE-3872 - Card software simulation

*/

#include "pitches.h"

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;  // the number of the pushbutton pin for LED
const int buttonPin2 = 3;  // the number of the pushbutton pin for motor
const int buttonPin3 = 4;  // the number of the pushbutton pin for speaker

const int speakerPin = 11; // the number of the speaker pushbutton pin
const int motorPin = 12; // the number of the motor pushbutton pin
const int ledPin = 13;    // the number of the LED pin
const int ledHeart = 10;    // the number of the LED pin hear

// variables will change:
int buttonState1 = 0;  // variable for reading the pushbutton 1 status
int buttonState2 = 0;  // variable for reading the pushbutton 2 status
int buttonState3 = 0;  // variable for reading the pushbutton 3 status

// for LED  fad
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

// speaker
int melody[] = {
NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,                   
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                 

NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                       

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, 0,
NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, END

};

// note durations: 8 = quarter note, 4 = 8th note, etc.
int noteDurations[] = {       //duration of the notes
8,4,8,4,
4,4,4,12,
4,4,4,4,4,4,
4,16,4,

8,4,8,4,
4,2,1,1,2,1,1,12,
4,4,4,4,4,4,
4,16,4,

4,4,4,4,4,4,
4,4,4,12,
4,4,4,4,4,4,
4,4,4,12,

4,4,4,4,4,4,
2,1,1,2,1,1,4,8,4,
2,6,4,2,6,4,
2,1,1,16,4,

4,8,4,4,4,
4,16,4,
4,8,4,4,4,
4,20,
};

int speed=90;  //higher value, slower notes

// note for another melody
int melody2[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations2[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// end speaker
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);

  // initialize the motor pin as an output:
  pinMode(motorPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT);

  // initialize the speaker pin as an output:
  pinMode(speakerPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin3, INPUT);  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  // run fad LED
  fadLed();
  
  // check if the pushbutton 1 is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    delay(5000);  // delay time on of LED
    fadLed();
    playspk(); //play speaker
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  // check if the pushbutton 2 is pressed. If it is, the buttonState is HIGH:
  if (buttonState3 == HIGH) {
    // turn motor on:
    digitalWrite(motorPin, HIGH);
    //delay(10000);  // delay time on of LED
  } else {
    // turn motor off:
    digitalWrite(motorPin, LOW);
  } 

  // check if the pushbutton 3 is pressed. If it is, the buttonState is HIGH:
  if (buttonState2 == HIGH) {
    // turn speaker on:
    //fadLed();
    playspk2();
  } 
} //end void loop

void playspk(){
  Serial.begin(9600);
  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

  int noteDuration = speed*noteDurations[thisNote];
  tone(speakerPin, melody[thisNote],noteDuration*.95);
  Serial.println(melody[thisNote]);

  delay(noteDuration);

  noTone(speakerPin);
}
}

void playspk2(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(speakerPin, melody2[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(speakerPin);
  }
}

void fadLed() {
    // set the brightness of pin 9:
    analogWrite(ledHeart, brightness);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}