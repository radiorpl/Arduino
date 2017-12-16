//src file for function to play wav in loop
//button stops or starts
//7/15/17

#include "Atm_wav_1.h"

//audio library
AudioPlaySdWav           playSdWav1;     //xy=401,325
AudioOutputI2S           i2s1;           //xy=777,323
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=745,592
// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Atm_wav_1& Atm_wav_1::begin( void ) {
  	// clang-format off
	static const state_t state_table[] PROGMEM = {
		/*               	ON_ENTER    ON_LOOP    ON_EXIT		EVT_BTN_1		ELSE */
		/*	WAV_1_ON */		ENT_WAV_1_ON,     -1,		-1,			WAV_1_OFF,	 -1,	  
		/*	WAV_1_OFF */	ENT_WAV_1_OFF,	  -1,		-1,			WAV_1_ON,	 -1,
	};
    // clang-format on
    Machine::begin( state_table, ELSE );
	
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
	//Atm_button
	Atm_button btn1;
	//_pin = pin;
	delay(1000);
    return *this;
	
}

int Atm_wav_1::event( int id ) {
  switch ( id ) {
    case EVT_BTN_1:
	return 0/*btn1.onPress()*/;  
  }
  return 0;
}
/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push( connectors, ON_PRESS, 0, <v>, <up> );
 */
void Atm_wav_1::action( int id ) {
	switch ( id ) {
		case ENT_WAV_1_ON:
			play();
			push( connectors, ON_PRESS, 0, 0, 0 );
			return;
		case ENT_WAV_1_OFF:
			stop();
			push( connectors, ON_PRESS, 0, 1, 0 );
			return;
	}	
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_wav_1& Atm_wav_1::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_wav_1::state( void ) {
  return Machine::state();
}

Atm_wav_1& Atm_wav_1::play( void ) {
	playSdWav1.play("DRONE1.WAV"); //play wav file
	delay(10);
	Serial.println("drone 1");
	return *this;
}

Atm_wav_1& Atm_wav_1::stop( void ) {
	playSdWav1.stop(); //stop wav file
	delay(10);
	Serial.println("stop");
	return *this;
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_wav_1& Atm_wav_1::btn_1() {
  trigger( EVT_BTN_1 );
  return *this;
}

/*
 * onPress() push connector variants ( slots 1, autostore 0, broadcast 0 )
 */

Atm_wav_1& Atm_wav_1::onPress( Machine& machine, int event ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, machine, event );
  return *this;
}

Atm_wav_1& Atm_wav_1::onPress( atm_cb_push_t callback, int idx ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, callback, idx );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_wav_1& Atm_wav_1::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "WAV_1\0EVT_BTN_1\0ELSE\0WAV_1_ON\0WAV_1_OFF" );
  return *this;
}
