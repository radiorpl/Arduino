//simple wav player using teensy audio library and audio adaptor 
//play wav activated by push of a button if nothing is currently 
//playing
//rich levinson 7/12/17
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=401,325
AudioOutputI2S           i2s1;           //xy=777,323
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=745,592
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

 elapsedMillis m_blinkTime; // Blink timer for the LED

//================set up=============

 void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  pinMode(0, INPUT_PULLUP);
  delay(1000);
}

//=========functions=========

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
  if (playSdWav1.isPlaying() == false && digitalRead(0) == LOW) {
    playSdWav1.play("DRONE2.WAV"); //play wav file
    delay(10); // wait for library to parse WAV info
    Serial.println("DRONE2.WAV");
  }
}
