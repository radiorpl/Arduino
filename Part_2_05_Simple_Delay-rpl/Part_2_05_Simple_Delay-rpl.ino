// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-5: Simple Delay


///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////
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
AudioPlaySdWav           playSdWav1;     //xy=70,88
AudioMixer4              mixer4;         //xy=188,203
AudioEffectDelay         delay1;         //xy=331,272
AudioMixer4              mixer2;         //xy=489,296
AudioMixer4              mixer1;         //xy=490,217
AudioMixer4              mixer3;         //xy=632,139
AudioOutputI2S           i2s1;           //xy=742,263
AudioConnection          patchCord1(playSdWav1, 0, mixer4, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer4, 1);
AudioConnection          patchCord3(mixer4, delay1);
AudioConnection          patchCord4(mixer4, 0, mixer3, 0);
AudioConnection          patchCord5(delay1, 0, mixer1, 0);
AudioConnection          patchCord6(delay1, 1, mixer1, 1);
AudioConnection          patchCord7(delay1, 2, mixer1, 2);
AudioConnection          patchCord8(delay1, 3, mixer1, 3);
AudioConnection          patchCord9(delay1, 4, mixer2, 0);
AudioConnection          patchCord10(delay1, 5, mixer2, 1);
AudioConnection          patchCord11(delay1, 6, mixer2, 2);
AudioConnection          patchCord12(delay1, 7, mixer2, 3);
AudioConnection          patchCord13(mixer2, 0, mixer3, 2);
AudioConnection          patchCord14(mixer1, 0, mixer3, 1);
AudioConnection          patchCord15(mixer3, 0, i2s1, 0);
AudioConnection          patchCord16(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=316,432
// GUItool: end automatically generated code


//from bira code
// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


void setup() {
  Serial.begin(9600);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
    }
  }
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.micGain(36);
  mixer1.gain(0, 0.2);
  mixer1.gain(1, 0.2);
  mixer1.gain(2, 0.2);
  mixer1.gain(3, 0.2);
  mixer2.gain(0, 0.2);
  mixer2.gain(1, 0.2);
  mixer2.gain(2, 0.2);
  mixer2.gain(3, 0.2);
  mixer3.gain(0, 0.5); // default = do not listen to direct signal
  mixer3.gain(1, 0.5); // ch1 is output of mixer1
  mixer3.gain(2, 0.5); // ch2 is output of mixer2
  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0.5);
  delay1.delay(0, 400);
  delay1.delay(1, 400);
  delay1.delay(2, 400);
  delay1.delay(3, 400);
  delay1.delay(4, 400);
  delay1.delay(5, 400);
  delay1.delay(6, 400);
  delay1.delay(7, 400);
  pinMode(13, OUTPUT); // LED on pin 13
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  delay(1000);
}

elapsedMillis blinkTime;

void loop() {
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
      playSdWav1.play("DRONE2.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE2.WAV");
      }

 // uncomment for A3 knob to control the feedback level
  /*
  int knob = analogRead(A3);
  float feedback = (float)knob / 1050.0;
  mixer1.gain(3, feedback);
  */
  
 // read the knob position (analog input A2)
  int knob = analogRead(A2);
  float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);


}




