//Ronald edit into fuctions
//Working Version 7/2/27
//Sounds Great!
//plays 2 wav files plus one delay object with feedback, delay time, and mix
//controls + send control for both wavs
//Add delay with multiple taps and fixed rhythms
//One track each channel (stereo)

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
AudioPlaySdWav           playSdWav1;     //xy=71,50
AudioPlaySdWav           playSdWav2;     //xy=69,560
AudioMixer4              mixer1;         //xy=236,49
AudioMixer4              mixer2;         //xy=313,181
AudioMixer4              mixer4;         //xy=327,476
AudioEffectDelay         delay1;         //xy=378,329
AudioMixer4              mixer5;         //xy=611,361
AudioMixer4              mixer3;         //xy=619,234
AudioMixer4              mixer6;         //xy=763,283
AudioOutputI2S           i2s1;           //xy=892,286
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer4, 0);
AudioConnection          patchCord4(playSdWav2, 1, mixer4, 1);
AudioConnection          patchCord5(mixer1, 0, mixer3, 0);
AudioConnection          patchCord6(mixer1, 0, mixer2, 0);
AudioConnection          patchCord7(mixer2, delay1);
AudioConnection          patchCord8(mixer4, 0, mixer5, 0);
AudioConnection          patchCord9(mixer4, 0, mixer2, 2);
AudioConnection          patchCord10(delay1, 0, mixer3, 1);
AudioConnection          patchCord11(delay1, 0, mixer5, 1);
AudioConnection          patchCord12(delay1, 0, mixer2, 1);
AudioConnection          patchCord13(delay1, 1, mixer3, 2);
AudioConnection          patchCord14(delay1, 1, mixer5, 2);
AudioConnection          patchCord15(delay1, 2, mixer3, 3);
AudioConnection          patchCord16(delay1, 2, mixer5, 3);
AudioConnection          patchCord17(mixer5, 0, mixer6, 1);
AudioConnection          patchCord18(mixer3, 0, mixer6, 0);
AudioConnection          patchCord19(mixer6, 0, i2s1, 0);
AudioConnection          patchCord20(mixer6, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=698,514
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

// Values for the delay
//                   Inital    1    2    3    4    5
const int delay_0[] = {   0, 107, 143, 214, 286, 425 };
const int delay_1[] = {   0,  54,  72, 107, 143, 213 };
const int delay_2[] = {   0,  72, 107, 143, 213, 286 };


////////////////////////////
// Variables
////////////////////////////
int m_sensorValue = 0; // Unused
//int m_sensorValue2 = 0;
int m_lastRange = -1; // Last position of the delay knob
//int m_lastRange2 = 0;
elapsedMillis m_blinkTime; // Blink timer for the LED

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
  mixer3.gain(0, 0.3);
  mixer3.gain(1, 0.3);
  mixer3.gain(2, 0.2);
  mixer3.gain(3, 0.2);
  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0.5);
  mixer5.gain(0, 0.3);
  mixer5.gain(1, 0.3);
  mixer5.gain(2, 0.2);
  mixer5.gain(3, 0.2);
  mixer6.gain(0, 0.5);
  mixer6.gain(1, 0.5);
  SetDelay(0);
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

void SetDelay(int range) {
  if ((m_lastRange != range) && (range >= 0) && (range <= 5)) {
    m_lastRange = range;
    delay1.delay(0, delay_0[range]);
    delay1.delay(1, delay_1[range]);
    delay1.delay(2, delay_2[range]);
  }
}

void CheckDelay() {
  // A6 knob to control the delay time
  int del = analogRead(A6);
  if ((lowerBound <= del) && (del < threshold1)) {
    SetDelay(1);
  }
  else if (del < threshold2) {
    SetDelay(2);
  }
  else if (del < threshold3) {
    SetDelay(3);
  }
  else if (del < threshold4) {
    SetDelay(4);
  }
  else if (del < threshold5) {
    SetDelay(5);
  }
}

void SetMasterVolume(int level) {
  // read the knob position for master volume(analog input A2)
  float vol = (float)level / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);
}

void SetFeedbackLevel(int level) {
  // uncomment for A3 knob to control the feedback level
  float feedback = (float)level / 1050.0;
  mixer2.gain(1, feedback);
}

void SetCrossfade(int mixKnob) {
  // crossfader/mix both wavs
  // knob = 0 to 1023
  float gain1 = (float)mixKnob / 1023.0;
  float gain2 = 1.0 - gain1;
  mixer3.gain(0, gain2);
  mixer3.gain(1, gain1);
  mixer5.gain(0, gain2);
  mixer5.gain(1, gain1);
}

void SetWav1Gain(int level) {
  // wav 1 effect send
  float gain = (float)level / 1023.0;
  mixer2.gain(0, gain);
}

void SetWav2Gain(int level) {
  // wav 2 effect send
  float gain = (float)level / 1023.0;
  mixer2.gain(2, gain);
}

void BlinkLED() {
  if (m_blinkTime < 250) {
    digitalWrite(13, LOW);
  } else if (m_blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    m_blinkTime = 0; // start blink cycle over again
  }
}

void loop() {
  BlinkLED();
  
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

  SetMasterVolume(analogRead(A2));

  SetFeedbackLevel(analogRead(A3));

  CheckDelay();

  SetCrossfade(analogRead(A7));

  SetWav1Gain(analogRead(A10));

  SetWav2Gain(analogRead(A11));

}

