/*************************************************** 
9-1-13 put pot read in the interupt time
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
#define RESET 9      // VS1053 reset pin (output)
#define CS 10        // VS1053 chip select pin (output)
#define DCS 8        // VS1053 Data/command select pin (output)
#define DREQ 3       // VS1053 Data request pin (into Arduino)
#define CARDCS 4     // Card chip select pin


Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(RESET, CS, DCS, DREQ, CARDCS);
// Alternately, use 'soft SPI'. Requires Adafruit's flexible SD library
// Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(MOSI, MISO, CLK, RESET, CS, DCS, DREQ, CARDCS);

// pot part

// these are constants that won't change while the code is running
const int lowerBound = 0;
const int threshold1 = 204;
const int threshold2 = 408;
const int threshold3 = 610;
const int threshold4 = 814;
const int threshold5 = 1024;
// these variables will change
int sensorValue = 0;
int lastRange = 0;
// end pot part

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Library Test");

  // initialise the music player
  if (!musicPlayer.begin()) {
    Serial.println("VS1053 not found");
    while (1);  // don't do anything more
  }


  if (!SD.begin(CARDCS)) {
    Serial.println("SD failed, or not present");
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  /***** Two interrupt options! *******/ 
  // This option uses timer0, this means timer1 & t2 are not required
  // (so you can use 'em for Servos, etc) BUT millis() can lose time
  // since we're hitchhiking on top of the millis() tracker
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);
  
  // This option uses a pin interrupt. No timers required! But DREQ
  // must be on an interrupt pin. For Uno/Duemilanove/Diecimilla
  // that's Digital #2 or #3
  // See http://arduino.cc/en/Reference/attachInterrupt for other pins
  // *** This method is preferred
  //if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT))
    //Serial.println("DREQ pin is not an interrupt pin");
}

void loop() {  
  // Alternately, we can just play an entire file at once
  // This doesn't happen in the background, instead, the entire
  // file is played and the program will continue when it's done!
  //next line is code commented out 
  //musicPlayer.playFullFile("track001.ogg");

  // Start playing a file, then we can do stuff while waiting for it to finish
  if (! musicPlayer.startPlayingFile("track001.mp3")) {  
      sensorValue = analogRead(0);
      byte i;
      static byte startPlayingFile = -1;
      
     
        if (lowerBound <= sensorValue && sensorValue < threshold1) {
    
    
        if (lastRange != 1) {
       
    
        if (startPlayingFile != 1) {
          startPlayingFile = 1;
          musicPlayer.startPlayingFile("DRONE1.WAV");
          Serial.println("Start DRONE1.WAV");
        }
    
    
          //lastRange = 1;
    
    
        }
    
    
      } 
    
    
      else if (threshold1 <= sensorValue && sensorValue < threshold2) {
    
    
        if (lastRange != 2) {
    
    
         if (startPlayingFile != 2) {
          startPlayingFile = 2;
          musicPlayer.startPlayingFile("DRONE2.WAV");
                Serial.println("start DRONE2.WAV");
          }
          //lastRange = 2;
    
    
        }
    
    
      }
    
    
      else if(threshold2 <= sensorValue && sensorValue <= threshold3) {
    
    
        if (lastRange != 3) {
    
    
         if (startPlayingFile != 3) {
          startPlayingFile = 3;
          musicPlayer.startPlayingFile("DRONE3.WAV");
                Serial.println("start DRONE3.WAV");
    }
          //lastRange = 3;
    
    
        }
    
    
      }
    
    
    
      else if(threshold3 <= sensorValue && sensorValue <= threshold4) {
    
    
        if (lastRange != 4) {
    
    
         if (startPlayingFile != 4) {
          startPlayingFile = 4;
          musicPlayer.startPlayingFile("DRONE4.WAV");
                Serial.println("start DRONE4.WAV");
    }
          //lastRange = 4;
    
    
        }
    
    
      }
      
      
      
       else if(threshold4 <= sensorValue && sensorValue <= threshold5) {
    
    
        if (lastRange != 5) {
    
    
         if (startPlayingFile != 5) {
          startPlayingFile = 5;
          musicPlayer.startPlayingFile("DRONE5.WAV");
                Serial.println("start DRONE5.WAV");
    }
          //lastRange = 5;
    
    
        }
    
    
      }
      
      delay(1000);
    }
        /*Serial.print(".");
        delay(1000);
      }
      Serial.println("Done playing music");
    }
    
        Serial.print("Could not open file");
        return;
      }
      Serial.println("Started playing");
      */

 while (musicPlayer.playingMusic) {
      sensorValue = analogRead(0);
      byte i;
      static byte startPlayingFile = -1;
      
     
        
        if (lowerBound <= sensorValue && sensorValue < threshold1) {
    
    
        if (lastRange != 1) {
       
    
        if (startPlayingFile != 1) {
          startPlayingFile = 1;
          musicPlayer.startPlayingFile("DRONE1.WAV");
          Serial.println("change toDRONE1.WAV");
        }
    
    
          //lastRange = 1;
    
    
        }
    
    
      } 
    
    
      else if (threshold1 <= sensorValue && sensorValue < threshold2) {
    
    
        if (lastRange != 2) {
    
    
         if (startPlayingFile != 2) {
          startPlayingFile = 2;
          musicPlayer.startPlayingFile("DRONE2.WAV");
                Serial.println("change toDRONE2.WAV");
          }
          //lastRange = 2;
    
    
        }
    
    
      }
    
    
      else if(threshold2 <= sensorValue && sensorValue <= threshold3) {
    
    
        if (lastRange != 3) {
    
    
         if (startPlayingFile != 3) {
          startPlayingFile = 3;
          musicPlayer.startPlayingFile("DRONE3.WAV");
                Serial.println("change to DRONE3.WAV");
    }
          //lastRange = 3;
    
    
        }
    
    
      }
    
    
    
      else if(threshold3 <= sensorValue && sensorValue <= threshold4) {
    
    
        if (lastRange != 4) {
    
    
         if (startPlayingFile != 4) {
          startPlayingFile = 4;
          musicPlayer.startPlayingFile("DRONE4.WAV");
                Serial.println("change to DRONE4.WAV");
    }
          //lastRange = 4;
    
    
        }
    
    
      }
      
      
      
       else if(threshold4 <= sensorValue && sensorValue <= threshold5) {
    
    
        if (lastRange != 5) {
    
    
         if (startPlayingFile != 5) {
          startPlayingFile = 5;
          musicPlayer.startPlayingFile("DRONE5.WAV");
                Serial.println("change to DRONE5.WAV");
    }
          //lastRange = 5;
    
    
        }
    
    
      }
      
      delay(1000);
    }
   }
