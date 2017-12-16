/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These can be any pins:
#define RESET 9      // VS1053 reset pin (output)
#define CS 10        // VS1053 chip select pin (output)
#define DCS 8        // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin


Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(RESET, CS, DCS, DREQ, CARDCS);
// pot part

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
  int sensorValue = 0;
int lastRange = 0;

// end pot part

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  musicPlayer.begin(); // initialise the music player
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play one file, don't return until complete
  musicPlayer.playFullFile("track001.mp3");
  // Play another file in the background, REQUIRES interrupts!
  musicPlayer.startPlayingFile("track002.mp3");
}
 void loop() {
 
  sensorValue = analogRead(0);
  byte i;
  static byte playing = -1;
  
 
    
    if (lowerBound <= sensorValue && sensorValue < threshold1) {


    if (lastRange != 1) {
   

    if (playing != 1) {
      playing = 1;
      musicPlayer.startPlayingFile("DRONE1.WAV");
      Serial.println("DRONE1.WAV");
    }


      //lastRange = 1;


    }


  } 


  else if (threshold1 <= sensorValue && sensorValue < threshold2) {


    if (lastRange != 2) {


     if (playing != 2) {
      playing = 2;
      musicPlayer.startPlayingFile("DRONE2.WAV");
            Serial.println("DRONE2.WAV");
      }
      //lastRange = 2;


    }


  }


  else if(threshold2 <= sensorValue && sensorValue <= threshold3) {


    if (lastRange != 3) {


     if (playing != 3) {
      playing = 3;
      musicPlayer.startPlayingFile("DRONE3.WAV");
            Serial.println("DRONE3.WAV");
}
      //lastRange = 3;


    }


  }



  else if(threshold3 <= sensorValue && sensorValue <= threshold4) {


    if (lastRange != 4) {


     if (playing != 4) {
      playing = 4;
      musicPlayer.startPlayingFile("DRONE4.WAV");
            Serial.println("DRONE4.WAV");
}
      //lastRange = 4;


    }


  }
  
  
  
   else if(threshold4 <= sensorValue && sensorValue <= threshold5) {


    if (lastRange != 5) {


     if (playing != 5) {
      playing = 5;
      musicPlayer.startPlayingFile("DRONE5.WAV");
            Serial.println("DRONE5.WAV");
}
      //lastRange = 5;


    }


  }
  
  delay(1000);
}

/*void loop() {
  // File is playing in the background
  if (! musicPlayer.playingMusic) 
    Serial.println("Done playing music");
  
  delay(1000);
}

void loop() {
  
 // File is playing in the background
  if (! musicPlayer.playingMusic) 
    Serial.println("Done playing music");
  
  delay(1000);
}*/
