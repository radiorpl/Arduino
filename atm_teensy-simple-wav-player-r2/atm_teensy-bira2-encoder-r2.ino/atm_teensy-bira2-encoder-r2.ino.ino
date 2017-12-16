
/*calls custom automation library to turn wav player on and off
7/16/17
modified to use encoders to move tracks up and down
works but way too sensitive, needs debouncing or something
7/20/17
added good working debounce to atm_encoder library
7/28/17
Works playing 2 instances of Atm_wav_1
8/2/17
Button toggles which instance a single encoder and button control
8/3/17
works with Atm_wav_1_multi_r0 and Atm_master_vol_r0
8/4/17
worker
*/
#include <Atm_wav_1.h>
#include <Atm_master_vol.h>
#include <Automaton.h>
//#include "audio_system_patch.h"

#define SDCARD_CS_PIN    10 // Use these with the Teensy Audio Shield
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Atm_wav_1 wav1;    //declare atm machines
Atm_wav_1 wav2;
Atm_master_vol vol;
Atm_encoder enc1;
Atm_encoder enc2;
Atm_button btn1;

const int  buttonPin = 3;      //non atm button
byte buttonPushCounter = 0;
byte buttonState = 0;
byte lastButtonState = 0;
byte encSwitch = 1;  //determines which instance encoder controls

void setup() {
   Serial.begin( 9600 );
   SPI.setMOSI(SDCARD_MOSI_PIN);
   SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
     while (1) {
       Serial.println("Unable to access the SD card");   
     }   
   }
   wav1.begin(1);    //start wav instances
   wav2.begin(2);
   vol.begin(1);
   enc1.begin(1, 0);
   enc2.begin(4, 6);
   enc2.onChange( ATM_DOWN, vol, vol.EVT_ENC_UP );
   enc2.onChange( ATM_UP, vol, vol.EVT_ENC_DOWN );
   enc2.debounce( 10 );  
   btn1.begin(2);
   pinMode(buttonPin, INPUT_PULLUP);
   wav1.trace(Serial);
   wav2.trace(Serial);
   vol.trace(Serial);
   //enc2.trace( Serial );
   btn1.trace(Serial);
}

void loop() {
  //control of encoder and button function
  if (encSwitch == 0){
    enc1.onChange( ATM_DOWN, wav1, wav1.EVT_ENC_UP );
    enc1.onChange( ATM_UP, wav1, wav1.EVT_ENC_DOWN );
    }
  else if (encSwitch == 1){
    enc1.onChange( ATM_DOWN, wav2, wav2.EVT_ENC_UP );
    enc1.onChange( ATM_UP, wav2, wav2.EVT_ENC_DOWN );      
    }
  if (encSwitch == 0){
    btn1.onPress( wav1, wav1.EVT_BTN_1 );
    }
  else if (encSwitch == 1){
    btn1.onPress( wav2, wav2.EVT_BTN_1 );
    }
  
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
      } 
    else {
      // if the current state is LOW then the button went from on to off:
      //Serial.println("off");
      }
      delay(50);// Delay a little bit to avoid bouncing    
  }
  lastButtonState = buttonState;
  if (buttonPushCounter > 1){
    buttonPushCounter = 0;
    //Serial.print("reset counter");
    //Serial.println(buttonPushCounter);
  }
  encSwitch = buttonPushCounter;
  //Serial.print("encSwitch = ");
  //Serial.println(encSwitch);
  
  automaton.run();
}
