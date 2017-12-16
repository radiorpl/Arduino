#include "Atm_enc_button.h"

Atm_enc_button& Atm_enc_button::begin(int encButton) {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*             	ON_ENTER  ON_LOOP  ON_EXIT  EVT_BTN_1  ELSE */
    /* COUNT_UP */ ENT_COUNT_UP,  -1,      -1,  COUNT_UP,   -1,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  encBtn = encButton;
  encButtonCounter1 = 0;
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_enc_button::event( int id ) {
  switch ( id ) {
    case EVT_BTN_1:
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_enc_button::action( int id ) {
  switch ( id ) {
	case ENT_COUNT_UP:
		//count++;
		return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_enc_button& Atm_enc_button::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_enc_button::state( void ) {
  return Machine::state();
}

Atm_enc_button& Atm_enc_button::count( void ) {
	if ( encBtn = 1 ) {
		encButtonCounter1++;
	}
	if ( encButtonCounter1 > 1 ){
		encButtonCounter1 = 0;
	}
  return *this;
}
/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_enc_button& Atm_enc_button::btn_1() {
  trigger( EVT_BTN_1 );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_enc_button& Atm_enc_button::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "MACHINE\0EVT_BTN_1\0ELSE\0COUNT_UP" );
  return *this;
}



 Automaton's home on Github 
