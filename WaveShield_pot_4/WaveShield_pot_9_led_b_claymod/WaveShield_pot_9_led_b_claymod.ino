 //3-27-13 Ambience box model A
//Dec 2013 adds diagnostic leds
//4-7-2014 switch no sd diagnostic to blink play light instead of having a different color
//1-6-16 10 tracks selected by pot instead of 5, for clay
#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"


SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play

WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

#define DEBOUNCE 5  // button debouncer

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {14, 15, 16, 17, 18, 19};
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'pressed' (the current state
volatile byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", "); 
  Serial.println(card.errorData(), HEX);
  while(1);
}




// pot part

// these are constants that won't change while the code is running
const int lowerBound = 0;
const int threshold1 = 93;
const int threshold2 = 186;
const int threshold3 = 279;
const int threshold4 = 372;
const int threshold5 = 465;
const int threshold6 = 558;
const int threshold7 = 651;
const int threshold8 = 744;
const int threshold9 = 837;
const int threshold10 = 930;
const int upperBound = 1024;
// these variables will change
  int sensorValue = 0;
int lastRange = 0;

// end pot part


void setup() {
  byte i;
  
  // set up serial port
  Serial.begin(9600);
  putstring_nl("WaveHC with ");
  Serial.print(NUMBUTTONS, DEC);
  putstring_nl("buttons");
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(freeRam());      // if this is under 150 bytes it may spell trouble!
  
  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
 
  // pin13 LED
  //pinMode(13, OUTPUT);
  //pin6 LED for diagnostics - No card found - removed 4/7/14
  //pinMode(6, OUTPUT);
  //pin7 LED for diagnostics - Playing if solid, no SD if blinks 3 times
  pinMode(7, OUTPUT);
  // Make input & enable pull-up resistors on switch pins
  for (i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  
  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);               // wait for a second
    digitalWrite(7, LOW);   
    delay(500);  
    digitalWrite(7, HIGH);
    delay(500); 
    digitalWrite(7, LOW);
    delay(500); 
    digitalWrite(7, HIGH);
    delay(500); 
    digitalWrite(7, LOW);
    delay(500);     
    digitalWrite(7, HIGH);
    delay(500); 
    digitalWrite(7, LOW);
    delay(500); 
    digitalWrite(7, HIGH);
    delay(500); 
    digitalWrite(7, LOW);
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Ready!");
  
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1<<TOIE2;


}

SIGNAL(TIMER2_OVF_vect) {
  check_switches();
}

void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  byte index;

  for (index = 0; index < NUMBUTTONS; index++) {
    currentstate[index] = digitalRead(buttons[index]);   // read the button
    
    /*     
    Serial.print(index, DEC);
    Serial.print(": cstate=");
    Serial.print(currentstate[index], DEC);
    Serial.print(", pstate=");
    Serial.print(previousstate[index], DEC);
    Serial.print(", press=");
    */
    
    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
          // just pressed
          justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
          // just released
          justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}


void loop() {
  digitalWrite(7, HIGH);   // turn the diagnostic LED on (HIGH is the voltage level)
  sensorValue = analogRead(0);
  byte i;
  static byte playing = -1;
  
 
    
    if (lowerBound <= sensorValue && sensorValue < threshold1) {


    if (lastRange != 1) {
   

    if (playing != 1) {
      playing = 1;
      playfile("SOUND1.WAV");
      Serial.println("SOUND1.WAV");
    }


      //lastRange = 1;


    }


  } 


  else if (threshold1 <= sensorValue && sensorValue < threshold2) {


    if (lastRange != 2) {


     if (playing != 2) {
      playing = 2;
      playfile("SOUND2.WAV");
            Serial.println("SOUND2.WAV");
      }
      //lastRange = 2;


    }


  }


  else if(threshold2 <= sensorValue && sensorValue <= threshold3) {


    if (lastRange != 3) {


     if (playing != 3) {
      playing = 3;
      playfile("SOUND3.WAV");
            Serial.println("SOUND3.WAV");
}
      //lastRange = 3;


    }


  }



  else if(threshold3 <= sensorValue && sensorValue <= threshold4) {


    if (lastRange != 4) {


     if (playing != 4) {
      playing = 4;
      playfile("SOUND4.WAV");
            Serial.println("SOUND4.WAV");
}
      //lastRange = 4;


    }


  }
  
  
  
   else if(threshold4 <= sensorValue && sensorValue <= threshold5) {


    if (lastRange != 5) {


     if (playing != 5) {
      playing = 5;
      playfile("SOUND5.WAV");
            Serial.println("SOUND5.WAV");
}
      //lastRange = 5;


    }


  }
  
 
   else if(threshold5 <= sensorValue && sensorValue <= threshold6) {


    if (lastRange != 6) {


     if (playing != 6) {
      playing = 6;
      playfile("SOUND6.WAV");
            Serial.println("SOUND6.WAV");
}
      lastRange = 6;

    }


  }


  else if(threshold6 <= sensorValue && sensorValue <= threshold7) {


    if (lastRange != 7) {


     if (playing != 7) {
      playing = 7;
      playfile("SOUND7.WAV");
            Serial.println("SOUND7.WAV");
}
      lastRange = 7;
      
          }


  }


  else if(threshold7 <= sensorValue && sensorValue <= threshold8) {


    if (lastRange != 8) {


     if (playing != 8) {
      playing = 8;
      playfile("SOUND8.WAV");
            Serial.println("SOUND8.WAV");
}
      lastRange = 8;
      
          }


  }

  else if(threshold8 <= sensorValue && sensorValue <= threshold9) {


    if (lastRange != 9) {


     if (playing != 9) {
      playing = 9;
      playfile("SOUND9.WAV");
            Serial.println("SOUND9.WAV");
}
      lastRange = 9;
      
          }


  }

  else if(threshold9 <= sensorValue && sensorValue <= upperBound) {


    if (lastRange != 10) {


     if (playing != 10) {
      playing = 10;
      playfile("SOUND10.WAV");
            Serial.println("SOUND10.WAV");
}
      lastRange = 10;
    }


  }
  
  
   


  if (! wave.isplaying) {
    playing = -1;
  
  }
  
  }
 

// Plays a full file from beginning   to end with no pause.
void playcomplete(char *name) {
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}


