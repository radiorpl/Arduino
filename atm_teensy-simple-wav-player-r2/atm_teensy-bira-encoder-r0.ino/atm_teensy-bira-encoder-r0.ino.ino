
/*calls custom automation library to turn wav player on and off
7/16/17
modified to use encoders to move tracks up and down
works but way too sensitive, needs debouncing or something
7/20/17
added good working debounce to atm_encoder library
7/28/17
*/
#include <Atm_wav_1.h>
#include <Automaton.h>



Atm_wav_1 wav1;
Atm_encoder enc1;


void setup() {

   Serial.begin( 9600 );
 

  wav1.begin();
  enc1.begin(  1, 0 )
   //.debounce( 20 )
   .onChange( ATM_DOWN, wav1, wav1.EVT_ENC_UP )
   .onChange( ATM_UP, wav1, wav1.EVT_ENC_DOWN );

    
    
  wav1.trace( Serial );
  enc1.trace( Serial );
}

void loop() {
  automaton.run();
}
