//Working Version 7/2/27
//Sounds Great!
//plays 2 wav files plus one delay object with feedback, delay time, and mix
//controls + send control for both wavs
//Add delay with multiple taps and fixed rhythms
//mono
//adds flanger and chorus as well as more mixers and routing

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


// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=69,49
AudioPlaySdWav           playSdWav2;     //xy=69,483
AudioMixer4              mixer1;         //xy=221,50
AudioMixer4              mixer4;         //xy=235,488
AudioEffectDelay         delay1;         //xy=289,326
AudioMixer4              mixer2;         //xy=313,181
AudioMixer4              mixer8;         //xy=537,601
AudioMixer4              mixer7;         //xy=541,483
AudioMixer4              mixer5;         //xy=611,361
AudioMixer4              mixer3;         //xy=619,234
AudioEffectFlange        flange1;        //xy=682,464
AudioEffectChorus        chorus1;        //xy=694,554
AudioMixer4              mixer6;         //xy=762,280
AudioOutputI2S           i2s1;           //xy=892,286
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer4, 0);
AudioConnection          patchCord4(playSdWav2, 1, mixer4, 1);
AudioConnection          patchCord5(mixer1, 0, mixer3, 0);
AudioConnection          patchCord6(mixer1, 0, mixer2, 0);
AudioConnection          patchCord7(mixer1, 0, mixer7, 0);
AudioConnection          patchCord8(mixer1, 0, mixer8, 0);
AudioConnection          patchCord9(mixer4, 0, mixer5, 0);
AudioConnection          patchCord10(mixer4, 0, mixer2, 2);
AudioConnection          patchCord11(mixer4, 0, mixer7, 1);
AudioConnection          patchCord12(mixer4, 0, mixer8, 1);
AudioConnection          patchCord13(delay1, 0, mixer3, 1);
AudioConnection          patchCord14(delay1, 0, mixer5, 1);
AudioConnection          patchCord15(delay1, 0, mixer2, 1);
AudioConnection          patchCord16(delay1, 1, mixer3, 2);
AudioConnection          patchCord17(delay1, 1, mixer5, 2);
AudioConnection          patchCord18(delay1, 2, mixer3, 3);
AudioConnection          patchCord19(delay1, 2, mixer5, 3);
AudioConnection          patchCord20(mixer2, delay1);
AudioConnection          patchCord21(mixer8, chorus1);
AudioConnection          patchCord22(mixer7, flange1);
AudioConnection          patchCord23(mixer5, 0, mixer6, 1);
AudioConnection          patchCord24(mixer3, 0, mixer6, 0);
AudioConnection          patchCord25(flange1, 0, mixer6, 2);
AudioConnection          patchCord26(chorus1, 0, mixer6, 3);
AudioConnection          patchCord27(mixer6, 0, i2s1, 0);
AudioConnection          patchCord28(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=898,592
// GUItool: end automatically generated code








// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
#define FLANGE_DELAY_LENGTH (2*AUDIO_BLOCK_SAMPLES) //from teensy documentation

//flange settings from teensy documentation
int s_idx = 2*FLANGE_DELAY_LENGTH/4;

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
  mixer1.gain(1, 0.5);
  mixer2.gain(0, 0.3);
  mixer2.gain(1, 0.3);
  mixer2.gain(2, 0.3);
  mixer3.gain(0, 0.5); //clean
  mixer3.gain(1, 0.0); //delay
  mixer3.gain(2, 0.0); //delay
  mixer3.gain(3, 0.0); //delay
  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0.5);
  mixer5.gain(0, 0.5); //clean
  mixer5.gain(1, 0.0); //delay
  mixer5.gain(2, 0.0); //delay
  mixer5.gain(3, 0.0); //delay
  mixer6.gain(0, 0.5); //clean signal 1/delay
  mixer6.gain(1, 0.0); //clean signal 2/delay
  mixer6.gain(2, 0.5); //flanger
  mixer6.gain(3, 0.0);   //chorus
  delay1.delay(0, 0.0);
  delay1.delay(1, 0.0);
  delay1.delay(2, 0.0);
  //flange1.begin();
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

  //play wav 1
      if (playSdWav1.isPlaying() == false) {
      playSdWav1.play("DRONE2.WAV"); //play wav file
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE2.WAV");
      }

  //play wav 2
      if (playSdWav2.isPlaying() == false) {
      playSdWav2.play("DRONE3.WAV"); //play wav file
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE3.WAV");
      }


  // read the knob position for master volume(analog input A2)
  int knob = analogRead(A2);
  float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);

/*
  // uncomment for A3 knob to control the feedback level
  int fb = analogRead(A3);
  float feedback = (float)fb / 1050.0;
  mixer2.gain(1, feedback);
*/
/*
  // uncomment for A6 knob to control the delay time 
  int del = analogRead(A6);
  if (lowerBound <= del && del < threshold1) {
   if (lastRange != 1) {
   delay1.delay(0, 107);
   delay1.delay(1, 54);
   delay1.delay(2, 72);
   }
  }
   else if (threshold1 <= del && del < threshold2) {
   if (lastRange != 2) {
   delay1.delay(0, 143);
   delay1.delay(1, 72);
   delay1.delay(2, 107);
   }
  }
    else if (threshold2 <= del && del < threshold3) {
   if (lastRange != 3) {
   delay1.delay(0, 214);
   delay1.delay(1, 107);
   delay1.delay(2, 143);
   }
  } 
 else if (threshold3 <= del && del < threshold4) {
   if (lastRange != 4) {
   delay1.delay(0, 286);
   delay1.delay(1, 143);
   delay1.delay(2, 213);
   }
  } 
  else if (threshold4 <= del && del < threshold5) {
   if (lastRange != 5) {
   delay1.delay(0, 425);
   delay1.delay(1, 213);
   delay1.delay(2, 286);
   }
  } 


  // crossfader/mix both wavs
  int mixKnob = analogRead(A7);  // knob = 0 to 1023
  float gain1 = (float)mixKnob / 1023.0;
  float gain2 = 1.0 - gain1;
  mixer3.gain(0, gain2);
  mixer3.gain(1, gain1);
  mixer5.gain(0, gain2);
  mixer5.gain(1, gain1);
*/

  //

  
  // wav 1 effect send
  int send1 = analogRead(A10);  // knob = 0 to 1023
  float gain3 = (float)send1 / 1023.0;
  mixer2.gain(0, gain3);

  // wav 2 effect send  
  int send2 = analogRead(A11);
  float gain4= (float)send2 / 1023.0;
  mixer2.gain(2, gain4);

  
}

   
   

