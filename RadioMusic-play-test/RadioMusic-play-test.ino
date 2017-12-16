/*
 RADIO MUSIC
 https://github.com/TomWhitwell/RadioMusic
 
 Audio out: Onboard DAC, teensy3.1 pin A14/DAC
 
 Bank Button: 2
 Bank LEDs 3,4,5,6
 Reset Button: 8  
 Reset LED 11 
 Reset CV input: 9 
 Channel Pot: A9 
 Channel CV: A8 // check 
 Time Pot: A7 
 Time CV: A6 // check 
 SD Card Connections: 
 SCLK 14
 MISO 12
 MOSI 7 
 SS   10 
 
 NB: Compile using modified versions of: 
 SD.cpp (found in the main Arduino package) 
 play_sd_raw.cpp  - In Teensy Audio Library 
 play_sc_raw.h    - In Teensy Audio Library 
 
 from:https://github.com/TomWhitwell/RadioMusic/tree/master/Collateral/Edited%20teensy%20files

 Additions and changes:
 2016 by Jouni Stenroos - jouni.stenroos@iki.fi 
 - New bank change mode
 - Removing 330 file limit
 - Improving reset
 - File sorting
 - Audio crossfade
 - Some refactoring and organization of code.
 
 */
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RadioMusic.h"
#include "AudioSystemHelpers.h"
#include "Settings.h"
//#include "LedControl.h"
//#include "FileScanner.h"
#include "AudioEngine.h"
//#include "Interface.h"
#include "PlayState.h"

#include <Audio.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
SDPlayPCM           	 playRaw1;     //xy=1384.9999771118164,1365.0000133514404
AudioOutputI2S           i2s1;           //xy=1733.333333333333,1374.9999999999998
AudioConnection          patchCord1(playRaw1, 0, i2s1, 0);
AudioConnection          patchCord2(playRaw1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1433.333333333333,1491.6666666666665
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
	AudioMemory(25);	    
    Serial.begin( 9600 );
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
     if (!(SD.begin(SDCARD_CS_PIN))) {              //TODO: change to start in different mode when sd missing
      while (1) {
        Serial.println("Unable to access the SD card");   
      }   
    }
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);	   //master volume
	playRaw1.begin();
	playRaw1.loopPlayback(false);
	
	delay(1000);
}
	
void loop() {
	

	
}

