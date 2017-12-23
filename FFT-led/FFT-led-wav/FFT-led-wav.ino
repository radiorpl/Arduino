#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=225,244
AudioMixer4              mixer1;         //xy=400,103
AudioAnalyzeFFT1024      fft1024_1;      //xy=586,81
AudioOutputI2S           i2s1;           //xy=649,244
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord3(playSdWav1, 1, i2s1, 1);
AudioConnection          patchCord4(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord5(mixer1, fft1024_1);
AudioControlSGTL5000     sgtl5000_1;     //xy=670,337
// GUItool: end automatically generated code



//to use line in, uncomment below
//const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

//fft range arrays
//set for 87 wide
int lowBound [3] = {2, 6, 13};					//lower frequency bounds for eq channels
int highBound[3] = {4, 11, 120};				//upper frequency bounds for eq channels
//int ledPin   [9] = {0, 1, 2, 3, 4, 5, 35, 36, 37};			//led pins, grouped in order, harder to hook up
int ledPin   [9] = {0, 3, 35, 1, 4, 36, 2, 5, 37};			//led pins, grouped for 3 pins per eq channel
int ledBright [6] = {0, 20, 50, 90, 170, 255};		//led brightness settings
int l; //number of leds for setup loop

void setup() {
  	AudioMemory(40);	    
    Serial.begin( 9600 );
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
     if (!(SD.begin(SDCARD_CS_PIN))) {              //TODO: change to start in different mode when sd missing
      while (1) {
        Serial.println("Unable to access the SD card");   
      }   
    }
  	for (l=0; l<9; l++) {		//initialize led pins
  		pinMode(ledPin[l], OUTPUT);
  	}
  	// Enable the audio shield and set the output volume.
  	sgtl5000_1.enable();
	//for line in uncomment below
  	//sgtl5000_1.inputSelect(myInput);
  	sgtl5000_1.volume(0.5);
  	// Configure the window algorithm to use
  	fft1024_1.windowFunction(AudioWindowHanning1024);
  	//fft1024_1.windowFunction(NULL);
	mixer1.gain(0, 2.0);
	mixer1.gain(1, 2.0);
}

void loop() {
	
	if (playSdWav1.isPlaying() == false){
		playSdWav1.play("1.WAV"); //play wav file
      	delay(10); // wait for library to parse WAV info
	}
	
	float n;	//level from fft
  	int i;	//equalizer band
  	int j;	//second led for eq meter display
  	int k;	//third led for eq
  	int b;	//brightness for led 1
  	int c;	//brightness of led 2
  	int d;	//brightness of led 3

 	if (fft1024_1.available()) {
	    // each time new FFT data is available
	    // print it all to the Arduino Serial Monitor
	    Serial.print("FFT: ");
		for (i=0; i<3; i++) {
			  j = i+3;		//skip to correct led in array
			  k = j+3;
		      n = fft1024_1.read(lowBound[i], highBound[i]);
		      if (n >= 0.02) {
				 if (0.02 < n <= 0.05){
					  b = 1;
					  c = 0;
					  d = 0;
				  }
				  else if (0.05 < n <= 0.08){
					  b = 3;
					  c = 0;
					  d = 0;
				  }
				  else if (0.08 < n <= 0.11){
					  b = 4;
					  c = 0;
					  d = 0;
				  }
				  else if (0.11 < n <= 0.15){
					  b = 5;
					  c = 0;
					  d = 0;
				  }
				  else if (0.15 < n <= 0.19){
					  b = 5;
					  c = 1;
					  d = 0;
				  }
				  else if (0.19 < n <= 0.23){
					  b = 5;
					  c = 2;
					  d = 0;
				  }
				  else if (0.23 < n <= 0.28){
					  b = 5;
					  c = 3;
					  d = 0;
				  }
				  else if (0.28 < n <= 0.33){
					  b = 5;
					  c = 4;
					  d = 0;
				  }
				  else if (0.33 < n <= 0.39){
					  b = 5;
					  c = 5;
					  d = 0;
				  }
				  else if (0.39 < n <= 0.45){
					  b = 5;
					  c = 5;
					  d = 1;
				  }
				  else if (0.45 < n <= 0.52){
					  b = 5;
					  c = 5;
					  d = 2;
				  }
				  else if (0.52 < n <= 0.59){
					  b = 5;
					  c = 5;
					  d = 3;
				  }
				  else if (0.59 < n <= 0.67){
					  b = 5;
					  c = 5;
					  d = 4;
				  }

				  else if (n > 0.67){
					  b = 5;
					  c = 5;
					  d = 5;
				  }
				  	digitalWriteFast(ledPin[i], ledBright[b]);
					digitalWriteFast(ledPin[j], ledBright[c]);
					digitalWriteFast(ledPin[k], ledBright[d]);
					Serial.print(n);
		        	Serial.print(" ");
					delay(50);
		      } 
			  else {
				  	digitalWriteFast(ledPin[i], ledBright[0]);
					digitalWriteFast(ledPin[j], ledBright[0]);
					digitalWriteFast(ledPin[k], ledBright[0]);
			    	Serial.print("  -  "); // don't print "0.00"
			  }
		 }
		 Serial.println();
		} 
 }
