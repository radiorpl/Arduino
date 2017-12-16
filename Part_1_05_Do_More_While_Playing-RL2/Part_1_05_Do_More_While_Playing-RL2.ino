// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 1-5: Respond to Pushbuttons & Volume Knob
//
// Do more while playing.  Monitor pushbuttons and adjust
// the volume.  Whe the buttons are pressed, stop playing
// the current file and skip to the next or previous.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

AudioPlaySdWav           playSdWav1;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

//Bounce button0 = Bounce(0, 15);
//Bounce button2 = Bounce(2, 15);  // 15 = 15 ms debounce time

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

// pot part
//!!!waveshield pot 9

// these are constants that won't change while the code is running
const int lowerBound = 0;
const int threshold1 = 204;
const int threshold2 = 408;
const int threshold3 = 610;
const int threshold4 = 814;
const int threshold5 = 1024;
//const int threshold6 = 678;
//const int threshold7 = 791;
//const int threshold8 = 904;
//const int threshold9 = 1017;
//const int upperBound = 1024;
// these variables will change
//int sensorValue = 0;
int lastRange = 0;

// end pot part

void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  delay(1000);
}

//int filenumber = 0;  // while file to play

const char * filelist[5] = {
  "DRONE1.WAV", "DRONE2.WAV", "DRONE3.WAV", "DRONE4.WAV", "DRONE5.WAV"
};

elapsedMillis blinkTime;

void loop() {
  /*
  if (playSdWav1.isPlaying() == false) {
    const char *filename = filelist[filenumber];
    filenumber = 0;
    if (filenumber >= 4) filenumber = 0;
    Serial.print("Start playing ");
    Serial.println(filename);
    playSdWav1.play(filename);
    delay(10); // wait for library to parse WAV info
  }
 */ 
  // blink the LED without delays
  if (blinkTime < 250) {
    digitalWrite(13, LOW);
  } else if (blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    blinkTime = 0; // start blink cycle over again
  }
  
  /*
  // read pushbuttons
  button0.update();
  if (button0.fallingEdge()) {
    playSdWav1.stop();
  }
  button2.update();
  if (button2.fallingEdge()) {
    playSdWav1.stop();
    filenumber = filenumber - 2;
    if (filenumber < 0) filenumber = filenumber + 4;
  }

*/
//track one
  int sensorValue = analogRead(A6);
  //Serial.print("Knob (pin A6) = ");
  //Serial.println(A6);
  //byte i;
  //static byte playing = -1;
    if (lowerBound <= sensorValue && sensorValue < threshold1) {
    if (lastRange != 1) 
    {
   // if (playSdWav1.isPlaying() == false) 
    {
    //const char *filename = filelist[filenumber];
   // filenumber = 0;
    Serial.print("Start playing ");
    Serial.println("DRONE1.WAV~");
    playSdWav1.play("DRONE1.WAV");
    delay(10); // wait for library to parse WAV info
  }
   //lastRange = 1;
    }
  } 
  //track 2
  
else if (threshold1 <= sensorValue && sensorValue < threshold2) {
   //if (lastRange != 2) 
   {
     //if (playSdWav1.isPlaying() == false) 
     {
   // const char *filename = filelist[filenumber];
    //filenumber = 1;
    Serial.print("Start playing ");
    Serial.println("DRONE2.WAV~");
    playSdWav1.play("DRONE2.WAV");
    delay(10); // wait for library to parse WAV info
  }

      //lastRange = 2;

    }

  }


 /* 
 else if(threshold2 <= sensorValue && sensorValue <= threshold3) {
  if (lastRange != 3) {
   if (playing != 3) {
      playing = 3;
      playfile("DRONE3.WAV");
            Serial.println("DRONE3.WAV");
}
      //lastRange = 3;

    }

  }

  else if(threshold3 <= sensorValue && sensorValue <= threshold4) {
    if (lastRange != 4) {
     if (playing != 4) {
      playing = 4;
      playfile("DRONE4.WAV");
            Serial.println("DRONE4.WAV");
}
      //lastRange = 4;
    }
  } 
   else if(threshold4 <= sensorValue && sensorValue <= threshold5) {
    if (lastRange != 5) {
  if (playing != 5) {
      playing = 5;
      playfile("DRONE5.WAV");
            Serial.println("DRONE5.WAV");
}
      //lastRange = 5;
    }
  }
  
  if (! wave.isplaying) {
    playing = -1;
  
  }
  
 }
 
 // Plays a full file from beginning   to end with no pause.
void playcomplete(char *name) {
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}
  
*/  
 // read the knob position (analog input A2)
  int knob = analogRead(A2);
  float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);
}




