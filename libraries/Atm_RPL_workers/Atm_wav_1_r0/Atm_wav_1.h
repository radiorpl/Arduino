//header file for function to play wav in loop
//button stops or starts
//7/15/17
#pragma once

#include <Automaton.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class Atm_wav_1 : public Machine {
	public:
		enum {WAV_1_ON, WAV_1_OFF}; //STATES
		enum {EVT_BTN_1, ELSE}; //EVENTS
		//enum {WAV_START, WAV_STOP}; //ACTIONS
		
		Atm_wav_1( void ) : Machine(){};
		Atm_wav_1& begin( void );
		Atm_wav_1& play( void );
		Atm_wav_1& stop( void );
		Atm_wav_1& trace( Stream& stream );
		Atm_wav_1& onPress( Machine& machine, int event = 0 );
		Atm_wav_1& onPress( atm_cb_push_t callback, int idx = 0 ); 
		Atm_wav_1& trigger( int event );
		int state( void );
		Atm_wav_1& btn_1( void );
		int pin;
		//Atm_wav_1& volume( int volume );
		
	private:
     	enum { ENT_WAV_1_ON, ENT_WAV_1_OFF }; // ACTIONS
     	enum { ON_PRESS, CONN_MAX }; // CONNECTORS
     	atm_connector connectors[CONN_MAX];
		int _pin;
		
     	int event( int id ); 
     	void action( int id );	
};
