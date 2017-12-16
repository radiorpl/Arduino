/*
8/3/17
Volume control for audio system Atm_wav_1 working in preset steps
8/6/17 
attempt to add separate controls for each instance
*/	
#include "Atm_master_vol.h"
//#include "audio_system.h"




Atm_master_vol& Atm_master_vol::begin( int volCon ) {
  	// clang-format off
	static const state_t state_table[] PROGMEM = {
		/*               	ON_ENTER    		ON_LOOP    	ON_EXIT		EVT_ENC_UP		EVT_ENC_DOWN		EVT_BTN_1	     	ELSE */
		/*	START_UP */		ENT_VOL_15, 			-1,		-1,			VOL_16,	  	 	VOL_14,					-1,					-1,	  
		/*	VOL_0 */		ENT_VOL_0, 				-1,		-1,			VOL_1,	  	 	-1,					-1,					-1,	  
		/*	VOL_1 */		ENT_VOL_1, 				-1,		-1,			VOL_2,	  	 	VOL_0,				-1,					-1,
		/*	VOL_2 */		ENT_VOL_2, 				-1,		-1,			VOL_3,	  	 	VOL_1,				-1,					-1,
		/*	VOL_3*/			ENT_VOL_3, 				-1,		-1,			VOL_4,	  	 	VOL_2,				-1,					-1,
		/*	VOL_4 */		ENT_VOL_4, 				-1,		-1,			VOL_5,	  	 	VOL_3,				-1,					-1,
		/*	VOL_5 */		ENT_VOL_5, 				-1,		-1,			VOL_6,	  	 	VOL_4,				-1,					-1,	  
		/*	VOL_6 */		ENT_VOL_6, 				-1,		-1,			VOL_7,	  	 	VOL_5,				-1,					-1,
		/*	VOL_7 */		ENT_VOL_7, 				-1,		-1,			VOL_8,	  	 	VOL_6,				-1,					-1,
		/*	VOL_8*/			ENT_VOL_8, 				-1,		-1,			VOL_9,	  	 	VOL_7,				-1,					-1,
		/*	VOL_9 */		ENT_VOL_9, 				-1,		-1,			VOL_10,	  	 	VOL_8,				-1,					-1,	
		/*	VOL_10 */		ENT_VOL_10, 			-1,		-1,			VOL_11,	  	 	VOL_9,				-1,					-1,	  
		/*	VOL_11 */		ENT_VOL_11, 			-1,		-1,			VOL_12,	  	 	VOL_10,				-1,					-1,
		/*	VOL_12 */		ENT_VOL_12, 			-1,		-1,			VOL_13,	  	 	VOL_11,				-1,					-1,
		/*	VOL_13*/		ENT_VOL_13, 			-1,		-1,			VOL_14,	  	 	VOL_12,				-1,					-1,
		/*	VOL_14 */		ENT_VOL_14, 			-1,		-1,			VOL_15,	  	 	VOL_13,				-1,					-1,
		/*	VOL_15 */		ENT_VOL_15, 			-1,		-1,			VOL_16,	  	 	VOL_14,				-1,					-1,	  
		/*	VOL_16 */		ENT_VOL_16, 			-1,		-1,			VOL_17,	  	 	VOL_15,				-1,					-1,
		/*	VOL_17 */		ENT_VOL_17, 			-1,		-1,			VOL_18,	  	 	VOL_16,				-1,					-1,
		/*	VOL_18*/		ENT_VOL_18,				-1,		-1,			VOL_19,	  	 	VOL_17,				-1,					-1,
		/*	VOL_19 */		ENT_VOL_19, 			-1,		-1,			VOL_20,	  	 	VOL_18,				-1,					-1,		
		/*	VOL_20 */		ENT_VOL_20, 				-1,		-1,			VOL_21,	  	 	VOL_19,				-1,					-1,	  
		/*	VOL_21 */		ENT_VOL_21, 				-1,		-1,			VOL_22,	  	 	VOL_20,				-1,					-1,
		/*	VOL_22 */		ENT_VOL_22, 				-1,		-1,			VOL_23,	  	 	VOL_21,				-1,					-1,
		/*	VOL_23*/		ENT_VOL_23, 				-1,		-1,			VOL_24,	  	 	VOL_22,				-1,					-1,
		/*	VOL_24 */		ENT_VOL_24, 				-1,		-1,			VOL_25,	  	 	VOL_23,				-1,					-1,
		/*	VOL_25 */		ENT_VOL_25, 				-1,		-1,			VOL_26,	  	 	VOL_24,				-1,					-1,	  
		/*	VOL_26 */		ENT_VOL_26, 				-1,		-1,			VOL_27,	  	 	VOL_25,				-1,					-1,
		/*	VOL_27 */		ENT_VOL_27, 				-1,		-1,			VOL_28,	  	 	VOL_26,				-1,					-1,
		/*	VOL_28*/		ENT_VOL_28, 				-1,		-1,			VOL_29,	  	 	VOL_27,				-1,					-1,
		/*	VOL_29 */		ENT_VOL_29, 				-1,		-1,			 -1,	  	 	VOL_28,				-1,					-1,	
		
		
	};
    // clang-format on
    Machine::begin( state_table, ELSE );
	volControl = volCon;
	AudioMemory(8);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);	    
	mixer1.gain(0, 0.5);
    mixer1.gain(1, 0.5);
    mixer2.gain(0, 0.5);
    mixer2.gain(1, 0.5);
	mixer3.gain(0, 0.5);
	mixer4.gain(0, 0.5);
	
    return *this;	
}

int Atm_master_vol::event( int id ) {
  switch ( id ) {
    case EVT_ENC_UP:
		return 0;  
    case EVT_ENC_DOWN:
		return 0;  
    case EVT_BTN_1:
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
void Atm_master_vol::action( int id ) {
	switch ( id ) {
		case ENT_VOL_0:
			setVolume(0.0);
			return;
		case ENT_VOL_1:
			setVolume(0.02);
			return;	
		case ENT_VOL_2:
			setVolume(0.04);
			return;
		case ENT_VOL_3:
			setVolume(0.06);
			return;	
		case ENT_VOL_4:
			setVolume(0.08);
			return;			
		case ENT_VOL_5:
			setVolume(0.1);
			return;
		case ENT_VOL_6:
			setVolume(0.12);
			return;	
		case ENT_VOL_7:
			setVolume(0.14);
			return;
		case ENT_VOL_8:
			setVolume(0.16);//
			return;	
		case ENT_VOL_9:
			setVolume(0.19);
			return;	
		case ENT_VOL_10:
			setVolume(0.22);
			return;
		case ENT_VOL_11:
			setVolume(0.25);
			return;	
		case ENT_VOL_12:
			setVolume(0.28);
			return;
		case ENT_VOL_13:
			setVolume(0.32);//
			return;	
		case ENT_VOL_14:
			setVolume(0.36);
			return;			
		case ENT_VOL_15:
			setVolume(0.4);
			return;
		case ENT_VOL_16:
			setVolume(0.42);
			return;	
		case ENT_VOL_17:
			setVolume(0.44);
			return;
		case ENT_VOL_18:
			setVolume(0.48);//
			return;	
		case ENT_VOL_19:
			setVolume(0.52);
			return;
		case ENT_VOL_20:
			setVolume(0.56);
			return;
		case ENT_VOL_21:
			setVolume(0.60);
			return;	
		case ENT_VOL_22:
			setVolume(0.64);
			return;
		case ENT_VOL_23:
			setVolume(0.66);//
			return;	
		case ENT_VOL_24:
			setVolume(0.68);
			return;			
		case ENT_VOL_25:
			setVolume(0.70);
			return;
		case ENT_VOL_26:
			setVolume(0.74);
			return;	
		case ENT_VOL_27:
			setVolume(0.76);
			return;
		case ENT_VOL_28:
			setVolume(0.78);
			return;	
		case ENT_VOL_29:
			setVolume(0.8);//
			return;				
		}					
		
}


/* Optionally override the default trigger() method
 * Control how your machine processes trigger
 */

Atm_master_vol& Atm_master_vol::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_master_vol::state( void ) {
  return Machine::state();
}

Atm_master_vol& Atm_master_vol::setVolume( float volume ) {
	if ( volControl == 0 ){  //master
	sgtl5000_1.volume(volume);
	Serial.println("master vol ");
	Serial.println(volume);
	}
	else if ( volControl == 1 ){  //wav1
	mixer3.gain(0, volume);
	Serial.println("bira 1 volume ");
	Serial.println(volume);
	}
	else if ( volControl == 2 ){  //wav2
	mixer4.gain(0, volume);
	Serial.println("bira 2 volume ");
	Serial.println(volume);
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
 * onPress() push connector variants ( slots 1, autostore 0, broadcast 0 )
 */

Atm_master_vol& Atm_master_vol::onPress( Machine& machine, int event ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, machine, event );
  return *this;
}

Atm_master_vol& Atm_master_vol::onPress( atm_cb_push_t callback, int idx ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, callback, idx );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_master_vol& Atm_master_vol::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "MASTER_VOL\0EVT_ENC_DOWN\0EVT_ENC_UP\0EVT_BTN_1\0ELSE\0VOL_0\0VOL_1\0VOL_5\0VOL_7\0VOL_10" );
  return *this;
}
