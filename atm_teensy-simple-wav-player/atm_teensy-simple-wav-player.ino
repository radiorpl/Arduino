//first attempt at combining automation and audio libraries
//this sketch works at task of turning wav on and off in response to button,
//but i don't think i am actually makings state changes, i'm just calling the 
//audio library stuff directly from the button function.
//I feel like it should be using the events or actions, but can't figure out how yet
//7/12/17 rich levinson

#include <Automaton.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=401,325
AudioOutputI2S           i2s1;           //xy=777,323
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=745,592
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

class Atm_simple_wav : public Machine {

  public:
      Atm_simple_wav( String track ) : Machine() {};
    
    //short pin;
    //atm_timer_millis timer;
    
    
    enum { IDLE, WAV_ON, WAV_OFF }; // STATES
    enum { PLAY_CHECK, EVT_ON, EVT_OFF, ELSE }; // EVENTS
    enum { WAV_START, WAV_STOP }; // ACTIONS

     Atm_simple_wav & begin() {
      const static state_t state_table[] PROGMEM = {
        /*            ON_ENTER    ON_LOOP  ON_EXIT  PLAY_CHECK  EVT_ON  EVT_OFF  ELSE */
        /* IDLE    */  WAV_STOP,        -1,      -1,      -1,  WAV_START,     -1,    -1,
        /* WAV_ON  */   WAV_START,      -1,      -1,   WAV_START,     -1,    IDLE,   -1,
        /* WAV_OFF */  WAV_STOP,        -1,      -1,    WAV_STOP,     -1,    IDLE,   -1,
      };
      Machine::begin( state_table, ELSE );
      
      track = "DRONE2.WAV";
     /* if ( playSdWav1.isPlaying() == false ) {
      playSdWav1.play(track); //play wav file
      delay(10); // wait for library to parse WAV info
      Serial.println(track);
      }
      */
      return *this;
     }

     int event ( int id ) {
      switch ( id ) {
        case PLAY_CHECK :
          return playSdWav1.isPlaying();
      }
      return 0;
     }


      void action( int id ) {
      switch ( id ) {
        case WAV_START :
          playSdWav1.play(track); //play wav file
          delay(10);
          return;
        case WAV_STOP :
           playSdWav1.stop(); //stop wav file
           delay(10);
          return;
      }
    }

      };
      
      void button_change( int idx, int v, int up ) {
      if ( v ) {
        if ( playSdWav1.isPlaying() == 1) { //If the wav is playing
        playSdWav1.stop(); //stop wav file
        Serial.println("stop");
      }
      else if ( playSdWav1.isPlaying() == 0) { //If the wav isn't playing
        playSdWav1.play("DRONE1.WAV"); //play wav file
        delay(10);
        Serial.println("drone 1");
      }
    }
  }

//===========main==============
//Atm_simple_wav ;
Atm_button button1;
void setup() {
  button1.begin( 0 )
     .onPress( button_change );
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");   
    }   
  }
   delay(1000);
}
  
void loop() {
  automaton.run();
}


