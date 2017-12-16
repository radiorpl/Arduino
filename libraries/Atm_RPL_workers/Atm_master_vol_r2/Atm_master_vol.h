#pragma once
/*
Works controlling master vol along with Atm_wav_1_loop_r0
*/


#include <Automaton.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
//#include <audio_system.h>


class Atm_master_vol : public Machine {
	public:
		enum { START_UP, VOL_0, VOL_1, VOL_2, VOL_3, VOL_4, VOL_5, VOL_6, VOL_7, VOL_8, VOL_9, VOL_10, VOL_11, VOL_12, VOL_13, VOL_14, VOL_15, VOL_16, VOL_17, VOL_18, VOL_19, VOL_20, VOL_21, VOL_22, VOL_23, VOL_24, VOL_25, VOL_26, VOL_27, VOL_28, VOL_29 }; //STATES
		enum { EVT_ENC_DOWN, EVT_ENC_UP, EVT_BTN_1, ELSE }; //EVENTS
		//enum {WAV_START, WAV_STOP}; //ACTIONS
		
		Atm_master_vol( void ) : Machine(){};
		Atm_master_vol& begin( void );
		Atm_master_vol& setMaster( void ); 
		Atm_master_vol& trace( Stream& stream );
		Atm_master_vol& onPress( Machine& machine, int event = 0 );
		Atm_master_vol& onPress( atm_cb_push_t callback, int idx = 0 ); 
		Atm_master_vol& trigger( int event );
		int state( void );
		//atm_counter controlCounter; 
		//Atm_wav_1& volume( int volume );
		
		
	private:
     	enum { ENT_VOL_0, ENT_VOL_1, ENT_VOL_2, ENT_VOL_3, ENT_VOL_4, ENT_VOL_5, ENT_VOL_6, ENT_VOL_7, ENT_VOL_8, ENT_VOL_9,ENT_VOL_10, ENT_VOL_11, ENT_VOL_12, ENT_VOL_13, ENT_VOL_14, ENT_VOL_15, ENT_VOL_16, ENT_VOL_17, ENT_VOL_18, ENT_VOL_19, ENT_VOL_20, ENT_VOL_21, ENT_VOL_22, ENT_VOL_23, ENT_VOL_24, ENT_VOL_25, ENT_VOL_26, ENT_VOL_27, ENT_VOL_28, ENT_VOL_29 }; // ACTIONS
     	enum { ON_PRESS, CONN_MAX }; // CONNECTORS
     	atm_connector connectors[CONN_MAX];
		AudioControlSGTL5000 sgtl5000_1;     //xy=744,575
		AudioMixer4              mixer1;         //xy=594,297
		AudioMixer4              mixer2;         //xy=591,395
     	int event( int id ); 
     	void action( int id );	
};
