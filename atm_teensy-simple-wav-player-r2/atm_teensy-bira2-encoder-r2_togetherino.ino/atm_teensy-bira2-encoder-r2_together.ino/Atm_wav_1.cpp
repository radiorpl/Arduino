/*
src file for function to play wav in loop
button stops or starts
7/15/17
loop function works by putting playCheck in ON_LOOP event 
added button skips tracks
added play function has input filename
7/19/17
changed to encoders to toggle tracks up and down
works but needs debouncing or something b/c encoder is too sensitive
8/1/17
added instances, this version with 2 instances
looping works
*/
#include "Atm_wav_1.h"
//#include "audio_system_patch.h"
//#include "audio_system.h"
//#include "Atm_master_vol.h"

Atm_wav_1& Atm_wav_1::begin( int instance ) {
  	// clang-format off
	static const state_t state_table[] PROGMEM = {
		/*               	ON_ENTER    		ON_LOOP    	ON_EXIT		EVT_ENC_UP		EVT_ENC_DOWN		EVT_BTN_1	EVT_PLAY_CHECK     	ELSE */
		/*	WAV_1_ON */		ENT_WAV_1_ON, 	ENT_PLAY_CHECK,		-1,		WAV_2_ON,	  	 	-1,				WAV_OFF,	WAV_1_ON,			-1,	  
		/*	WAV_2_ON */		ENT_WAV_2_ON, 	ENT_PLAY_CHECK,		-1,		WAV_3_ON,	  	 WAV_1_ON,			WAV_OFF,	WAV_2_ON,			-1,
		/*	WAV_3_ON */		ENT_WAV_3_ON, 	ENT_PLAY_CHECK,		-1,		WAV_4_ON,	  	 WAV_2_ON,			WAV_OFF,	WAV_3_ON,			-1,
		/*	WAV_4_ON */		ENT_WAV_4_ON, 	ENT_PLAY_CHECK,		-1,		WAV_5_ON,	  	 WAV_3_ON,			WAV_OFF,	WAV_4_ON,			-1,
		/*	WAV_5_ON */		ENT_WAV_5_ON, 	ENT_PLAY_CHECK,		-1,		-1,	  	 		 WAV_4_ON,			WAV_OFF,	WAV_5_ON,			-1,
		/*	WAV_OFF */		ENT_WAV_OFF,		-1,				-1,		-1,	 				-1,				WAV_1_ON,		-1,				-1,
		
		
		
	};
    // clang-format on
    Machine::begin( state_table, ELSE );	//r2 moved audio setup to master vol
	playerNo = instance; 
    return *this;	
}

int Atm_wav_1::event( int id ) {
  switch ( id ) {
    case EVT_ENC_UP:
		return 0;  
    case EVT_ENC_DOWN:
		return 0;  
    case EVT_BTN_1:
		return 0;  
    case EVT_PLAY_CHECK: 
		return 0;
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
			play("DRONE1.WAV");
			return;
		case ENT_WAV_2_ON:
			play("DRONE2.WAV");
			return;
		case ENT_WAV_3_ON:
			play("DRONE3.WAV");
			return;	
		case ENT_WAV_4_ON:
			play("DRONE4.WAV");
			return;
		case ENT_WAV_5_ON:
			play("DRONE5.WAV");
			return;				
		case ENT_WAV_OFF:
			stop();
			return;
		case ENT_PLAY_CHECK:
			playCheck();
			return;
	}	
}

/* Optionally override the default trigger() method
 * Control how your machine processes trigger
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

Atm_wav_1& Atm_wav_1::play( const char *filename ) {	
	if ( playerNo == 1 ){
		playSdWav1.play( filename ); //play wav file
	}
	else if ( playerNo == 2){
		playSdWav2.play( filename ); //play wav file
	}
	delay(10);
	Serial.println( filename );
	return *this;
}


Atm_wav_1& Atm_wav_1::stop( void ) {
	if ( playerNo == 1 ){
	playSdWav1.stop(); //stop wav file
	Serial.println("stop 1");
	}
	else if ( playerNo == 2 ){
	playSdWav2.stop(); //stop wav file
	Serial.println("stop 2");
	}
	return *this;
}

Atm_wav_1& Atm_wav_1::playCheck( void ) {
	
	if ( playerNo == 1 && playSdWav1.isPlaying() == false ) { //doesn't stop trigger with true/false or 0/1
		trigger( EVT_PLAY_CHECK );
		Serial.println("playCheck");
	}
	else if ( playerNo == 2 && playSdWav2.isPlaying() == false ) { //doesn't stop trigger with true/false or 0/1
		trigger( EVT_PLAY_CHECK );
		Serial.println("playCheck");
	}		
	return *this;
}
/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */
/*
Atm_wav_1& Atm_wav_1::btn_1() {
  trigger( EVT_BTN_1 );
  return *this;
}
*/
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
    "WAV_1\0EVT_ENC_UP\0EVT_ENC_DOWN\0EVT_BTN_1\0EVT_PLAY_CHECK\0ELSE\0WAV_1_ON\0WAV_2_ON\0WAV_3_ON\0WAV_4_ON\0WAV_5_ON\0WAV_OFF" );
  return *this;
}
/*
Atm_led& Atm_led::trigger( int event ) {
  if ( event > ELSE ) {
    play();
  } else {
    Machine::trigger( event );
  }
  return *this;
}
*/
