//calls custom automation library to turn wav player on and off
//works!
//7/16/17
#include <Atm_wav_1.h>
#include <Automaton.h>

Atm_wav_1 wav1;
Atm_button btn1;
Atm_controller looper;

void setup() {

  // Serial.begin( 9600 );
  // trafficlight.trace( Serial );

  wav1.begin();
  btn1.begin( 0 )
   .onPress( wav1, wav1.EVT_BTN_1 );
  wav1.trace( Serial );
  /*looper.begin()
        .IF( playCheck() == false )
        .onChange( false, wav1, wav1.EVT_PLAY_CHECK );*/
}

void loop() {
  automaton.run();
}
