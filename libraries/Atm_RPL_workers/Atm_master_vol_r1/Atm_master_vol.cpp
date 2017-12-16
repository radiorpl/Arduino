/*
8/3/17
Volume control for audio system Atm_wav_1 working in preset steps
note:should decrease encoder debounce for volume controls
*/	
#include "Atm_master_vol.h"


/*
//audio library
AudioPlaySdWav           playSdWav1;     //xy=394,289
AudioPlaySdWav           playSdWav2;     //xy=398,385
AudioMixer4              mixer1;         //xy=594,297
AudioMixer4              mixer2;         //xy=591,395
AudioOutputI2S           i2s1;           //xy=824,334
*/




Atm_master_vol& Atm_master_vol::begin( void ) {
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
	AudioMemory(8);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.5);	
	AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
	AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
	AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
	AudioConnection          patchCord4(playSdWav2, 1, mixer2, 3);
	AudioConnection          patchCord5(mixer2, 0, i2s1, 1);
	AudioConnection          patchCord6(mixer1, 0, i2s1, 0);
    mixer1.gain(0, 0.5);
    mixer1.gain(1, 0.5);
    mixer2.gain(0, 0.5);
    mixer2.gain(1, 0.5);
	
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
			sgtl5000_1.volume(0.0);//
			return;
		case ENT_VOL_1:
			sgtl5000_1.volume(0.02);
			return;	
		case ENT_VOL_2:
			sgtl5000_1.volume(0.04);
			return;
		case ENT_VOL_3:
			sgtl5000_1.volume(0.06);
			return;	
		case ENT_VOL_4:
			sgtl5000_1.volume(0.08);
			return;			
		case ENT_VOL_5:
			sgtl5000_1.volume(0.1);
			return;
		case ENT_VOL_6:
			sgtl5000_1.volume(0.12);
			return;	
		case ENT_VOL_7:
			sgtl5000_1.volume(0.14);
			return;
		case ENT_VOL_8:
			sgtl5000_1.volume(0.16);//
			return;	
		case ENT_VOL_9:
			sgtl5000_1.volume(0.19);
			return;	
		case ENT_VOL_10:
			sgtl5000_1.volume(0.22);
			return;
		case ENT_VOL_11:
			sgtl5000_1.volume(0.25);
			return;	
		case ENT_VOL_12:
			sgtl5000_1.volume(0.28);
			return;
		case ENT_VOL_13:
			sgtl5000_1.volume(0.32);//
			return;	
		case ENT_VOL_14:
			sgtl5000_1.volume(0.36);
			return;			
		case ENT_VOL_15:
			sgtl5000_1.volume(0.4);
			return;
		case ENT_VOL_16:
			sgtl5000_1.volume(0.42);
			return;	
		case ENT_VOL_17:
			sgtl5000_1.volume(0.44);
			return;
		case ENT_VOL_18:
			sgtl5000_1.volume(0.48);//
			return;	
		case ENT_VOL_19:
			sgtl5000_1.volume(0.52);
			return;
		case ENT_VOL_20:
			sgtl5000_1.volume(0.56);
			return;
		case ENT_VOL_21:
			sgtl5000_1.volume(0.60);
			return;	
		case ENT_VOL_22:
			sgtl5000_1.volume(0.64);
			return;
		case ENT_VOL_23:
			sgtl5000_1.volume(0.66);//
			return;	
		case ENT_VOL_24:
			sgtl5000_1.volume(0.68);
			return;			
		case ENT_VOL_25:
			sgtl5000_1.volume(0.70);
			return;
		case ENT_VOL_26:
			sgtl5000_1.volume(0.74);
			return;	
		case ENT_VOL_27:
			sgtl5000_1.volume(0.76);
			return;
		case ENT_VOL_28:
			sgtl5000_1.volume(0.78);
			return;	
		case ENT_VOL_29:
			sgtl5000_1.volume(0.8);//
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
