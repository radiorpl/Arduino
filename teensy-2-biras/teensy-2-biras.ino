#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=154,323
AudioPlaySdWav           playSdWav1;     //xy=157,200
AudioMixer4              mixer1;         //xy=330,244
AudioMixer4              mixer2;         //xy=331,321
AudioOutputI2S           i2s1;           //xy=500,248
AudioConnection          patchCord1(playSdWav2, 0, mixer2, 0);
AudioConnection          patchCord2(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=339,418
// GUItool: end automatically generated code


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
int sensorValue2 = 0;
int lastRange = 0;
int lastRange2 = 0;

/////////////MAIN SKETCH////////////////////////////

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
/*
int filenumber = 0;  // while file to play

const char * filelist[5] = {
  "DRONE1.WAV", "DRONE2.WAV", "DRONE3.WAV", "DRONE4.WAV", "DRONE5.WAV"
};
*/
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

//read knob and play tracks  
int sensorValue = analogRead(A3);
//byte i;
static byte playing = -1;

//track 1
   if (lowerBound <= sensorValue && sensorValue < threshold1) {
   if (lastRange != 1) {
   if (playing != 1); {
      playing = 1;
      lastRange = 1;
      playSdWav1.play("DRONE1.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE1.WAV");
    }
  }
}
   
//track 2
    else if (threshold1 <= sensorValue && sensorValue < threshold2) {
   if (lastRange != 2) {
   if (playing != 2); {
      playing = 2;
      lastRange = 2;
      playSdWav1.play("DRONE2.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE2.WAV");
    }
  }
}

//track 3
   else if (threshold2 <= sensorValue && sensorValue < threshold3) {
   if (lastRange != 3) {
   if (playing != 3); {
      playing = 3;
      lastRange = 3;
      playSdWav1.play("DRONE3.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE3.WAV");
    }
  }
}

//track 4
   else if (threshold3 <= sensorValue && sensorValue < threshold4) {
   if (lastRange != 4) {
   if (playing != 4); {
      playing = 4;
      lastRange = 4;
      playSdWav1.play("DRONE4.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE4.WAV");
    }
  }
}

//track 5
   else if (threshold4 <= sensorValue && sensorValue < threshold5) {
   if (lastRange != 5) {
   if (playing != 5); {
      playing = 5;
      lastRange = 5;
      playSdWav1.play("DRONE5.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE5.WAV");
    }
  }
}

//loop
    if (playSdWav1.isPlaying() == false) {
      lastRange = 0;
      Serial.println("supposed to be looping");
    }
    
 
 // read the knob position (analog input A2)
  int knob = analogRead(A2);
  float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(vol);
  //Serial.print("volume = ");
  //Serial.println(vol);


//
 //----------------------------WAV2-----------------------------
//


//read knob and play tracks  
int sensorValue2 = analogRead(A6);
//byte2 i;
static byte playing2 = -1;

//track 1
   if (lowerBound <= sensorValue2 && sensorValue2 < threshold1) {
   if (lastRange2 != 1) {
   if (playing2 != 1); {
      playing2 = 1;
      lastRange2 = 1;
      playSdWav2.play("DRONE1.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE1.WAV number 2");
    }
  }
}
   
//track 2
    else if (threshold1 <= sensorValue2 && sensorValue2 < threshold2) {
   if (lastRange2 != 2) {
   if (playing2 != 2); {
      playing2 = 2;
      lastRange2 = 2;
      playSdWav2.play("DRONE2.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE2.WAV number 2");
    }
  }
}

//track 3
   else if (threshold2 <= sensorValue2 && sensorValue2 < threshold3) {
   if (lastRange2 != 3) {
   if (playing2 != 3); {
      playing2 = 3;
      lastRange2 = 3;
      playSdWav2.play("DRONE3.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE3.WAV number 2");
    }
  }
}

//track 4
   else if (threshold3 <= sensorValue2 && sensorValue2 < threshold4) {
   if (lastRange2 != 4) {
   if (playing2 != 4); {
      playing2 = 4;
      lastRange2 = 4;
      playSdWav2.play("DRONE4.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE4.WAV number 2");
    }
  }
}

//track 5
   else if (threshold4 <= sensorValue2 && sensorValue2 < threshold5) {
   if (lastRange2 != 5) {
   if (playing2 != 5); {
      playing2 = 5;
      lastRange2 = 5;
      playSdWav2.play("DRONE5.WAV");
      delay(10); // wait for library to parse WAV info
      Serial.println("DRONE5.WAV number 2");
    }
  }
}

//loop
    if (playSdWav2.isPlaying() == false) {
      lastRange2 = 0;
      Serial.println("supposed to be looping NUMBER 2");
    }
}
