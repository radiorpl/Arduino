#pragma once

#include <Automaton.h>

class Atm_encoder : public Machine {
 public:
  enum { IDLE, WAIT_UP_1_DB, WAIT_UP_1, WAIT_UP_2_DB, WAIT_UP_2, WAIT_UP_3_DB, WAIT_UP_3, WAIT_UP_4_DB, WAIT_UP_4, WAIT_UP_DB, WAIT_DOWN_1_DB, WAIT_DOWN_1, WAIT_DOWN_2_DB, WAIT_DOWN_2, WAIT_DOWN_3_DB, WAIT_DOWN_3, WAIT_DOWN_4_DB, WAIT_DOWN_4, WAIT_DOWN_DB, UP, DOWN };          // STATES
  enum { EVT_TIMER, EVT_UP, EVT_DOWN, ELSE };  // EVENTS

  Atm_encoder( void ) : Machine(){}; 
  Atm_encoder& begin( int pin1, int pin2, int divider = 1 );
  Atm_encoder& trace( Stream& stream );
  Atm_encoder& onChange( Machine& machine, int event = 0 );
  Atm_encoder& onChange( atm_cb_push_t callback, int idx = 0 );
  Atm_encoder& onChange( bool status, Machine& machine, int event = 0 );
  Atm_encoder& onChange( bool status, atm_cb_push_t callback, int idx = 0 );
  int state( void );
  Atm_encoder& range( int min, int max, bool wrap = false );
  Atm_encoder& set( int value );
  Atm_encoder& debounce( int delay );

 private:
  enum { LP_IDLE, ENT_UP, ENT_DOWN };  // ACTIONS
  static const int DEBOUNCE = 2;
  short pin1, pin2;
  const static char enc_states[];
  uint8_t enc_bits;
  int8_t enc_counter;
  int8_t enc_direction;
  int divider;
  int value, min, max;
  bool wrap, range_invert;
  atm_connector onup, ondown;
  atm_timer_millis timer_debounce;

  bool count( int direction );
  int event( int id );
  void action( int id );
};
