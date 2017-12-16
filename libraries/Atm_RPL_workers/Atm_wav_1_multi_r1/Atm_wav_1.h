/*
header file for function to play wav in loop
button stops or starts
7/15/17
loop function works by putting playCheck in ON_LOOP event 
added button skips tracks
added play function has input filename
7/19/17
added instances, this version with 2 instances
looping works
8/1/17
*/

#pragma once

#include <Automaton.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Atm_master_vol.h>


class Atm_wav_1 : public Machine {
	public:
		enum { WAV_1_ON, WAV_2_ON, WAV_3_ON, WAV_4_ON, WAV_5_ON, WAV_OFF }; //STATES
		enum { EVT_ENC_DOWN, EVT_ENC_UP, EVT_BTN_1, EVT_PLAY_CHECK, ELSE }; //EVENTS
		//enum {WAV_START, WAV_STOP}; //ACTIONS
		
		Atm_wav_1( void ) : Machine(){};
		Atm_wav_1& begin( int instance );
		Atm_wav_1& play( const char *filename ); 
		Atm_wav_1& stop( void );
		Atm_wav_1& playCheck( void );
		Atm_wav_1& trace( Stream& stream );
		Atm_wav_1& onPress( Machine& machine, int event = 0 );
		Atm_wav_1& onPress( atm_cb_push_t callback, int idx = 0 ); 
		Atm_wav_1& trigger( int event );
		int state( void );
		//atm_counter controlCounter; 
		//Atm_wav_1& volume( int volume );
		//AudioControlSGTL5000     sgtl5000_1;     //xy=744,575
		AudioPlaySdWav           playSdWav1;     //xy=394,289
		AudioPlaySdWav           playSdWav2;     //xy=398,385
		AudioMixer4              mixer1;         //xy=594,297
		AudioMixer4              mixer2;         //xy=591,395
		AudioOutputI2S           i2s1;           //xy=824,334
	private:
     	enum { ENT_WAV_1_ON, ENT_WAV_2_ON, ENT_WAV_3_ON, ENT_WAV_4_ON, ENT_WAV_5_ON, ENT_WAV_OFF, ENT_PLAY_CHECK }; // ACTIONS
     	enum { ON_PRESS, CONN_MAX }; // CONNECTORS
     	atm_connector connectors[CONN_MAX];
		byte playerNo;
		
     	int event( int id ); 
     	void action( int id );	
};
