/*
Midi Keyboard Proof 
based on
MIDI On/Off Messages
By Amanda Ghassaei
July 2012
Mod Feb 2015 Rich Levinson for button trigger
http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

*/
 
 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
 int noteON = 144; //144 = 10010000 in binary, note on command
 int noteOFF = 128; //128 = 10000000 in binary, note off command
 int note=60; //middle C
 const int buttonPin = 2;     // the number of the pushbutton pin
 const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
void setup() {
  //  Set MIDI baud rate:
  Serial.begin(31250);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    //send midi note
    MIDImessage(noteON, note, velocity);//turn note on
    } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    //don't send midi 
    MIDImessage(noteOFF, note, velocity);//turn note off
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

