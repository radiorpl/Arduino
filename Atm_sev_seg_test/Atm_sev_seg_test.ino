#include <Atm_sev_seg.h> 
#include <Automaton.h>

Atm_sev_seg ssd;
Atm_button btn;

void setup() {
  ssd.begin();
  btn.begin(0);
  btn.onPress( ssd, ssd.EVT_BTN_1);
}

void loop() {
  automaton.run();
}
