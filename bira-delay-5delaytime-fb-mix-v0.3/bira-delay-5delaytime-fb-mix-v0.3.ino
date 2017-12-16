//Working version 7/2/17
//plays wav file plus delay with feedback, delay time, and mix
//controls
// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-6: Feedback (Echo) Delay

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=69,144
AudioMixer4              mixer1;         //xy=269,74
AudioMixer4              mixer2;         //xy=289,200
AudioEffectDelay         delay1;         //xy=456,390
AudioMixer4              mixer3;         //xy=517,195
AudioOutputI2S           i2s1;           //xy=742,263
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, mixer3, 0);
AudioConnection          patchCord4(mixer1, 0, mixer2, 0);
AudioConnection          patchCord5(mixer2, delay1);
AudioConnection          patchCord6(delay1, 0, mixer2, 1);
AudioConnection          patchCord7(delay1, 0, mixer3, 1);
AudioConnection          patchCord8(mixer3, 0, i2s1, 0);
AudioConnection          patchCord9(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=290,651
// GUItool: end automatically generated code





// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Number of samples to average with each ADC reading.
const int ANALOG_READ_AVERAGING = 32; 


// threshold settings for track selection pot
// these are constants that won't change while the code is running
const int lowerBound = 0;
const int threshold1 = 204;
const int threshold2 = 408;
const int threshold3 = 610;
const int threshold4 = 814;
const int threshold5 = 1024;
// these variables will change
int sensorValue = 0;
//int sensorValue2 = 0;
int lastRange = 0;
//int lastRange2 = 0;
 
///////MAIN SKETCH//////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  mixer1.gain(0, 0.5);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  delay1.delay(0, 0.0);
    SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  analogReadAveraging(ANALOG_READ_AVERAGING);
  delay(1000);
}

elapsedMillis blinkTime;

void loop() {
  //BLINKING LED
  // blink the LED without delays
  if (blinkTime < 250) {
    digitalWrite(13, LOW);
  } else if (blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    blinkTime = 0; // start blink cycle over again
  }

  //play wav
      if (playSdWav1.isPlaying() == false) {
      playSdWav1.play("DRONE2.WAV"); //play wav file
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE2.WAV");
      }

  // read the knob position for master volume(analog input A2)
  int knob = analogRead(A2);
  float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);
  
  // uncomment for A3 knob to control the feedback level
  
  int fb = analogRead(A3);
  float feedback = (float)fb / 1050.0;
  mixer2.gain(1, feedback);

  // uncomment for A6 knob to control the delay time 
  
  int del = analogRead(A6);
  if (lowerBound <= del && del < threshold1) {
   if (lastRange != 1) {
   delay1.delay(0, 107);
   }
  }
   else if (threshold1 <= del && del < threshold2) {
   if (lastRange != 2) {
   delay1.delay(0, 143);
   }
  }
    else if (threshold2 <= del && del < threshold3) {
   if (lastRange != 3) {
   delay1.delay(0, 214);
   }
  } 
 else if (threshold3 <= del && del < threshold4) {
   if (lastRange != 4) {
   delay1.delay(0, 286);
   }
  } 
  else if (threshold4 <= del && del < threshold5) {
   if (lastRange != 5) {
   delay1.delay(0, 425);
   }
  } 

  // crossfader/mix

  int mixKnob = analogRead(A7);  // knob = 0 to 1023
  float gain1 = (float)mixKnob / 1023.0;
  float gain2 = 1.0 - gain1;
  mixer3.gain(0, gain2);
  //mixer2.gain(1, gain2);
  mixer3.gain(1, gain1);
  //mixer2.gain(1, gain2);

  

  
}

   
   

