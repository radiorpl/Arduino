/*
// FFT Test
//
// Compute a 1024 point Fast Fourier Transform (spectrum analysis)
// on audio connected to the Left Line-In pin.  By changing code,
// a synthetic sine wave can be input instead.
//
// This example code is in the public domain.

Adapted from fft example for teensy audio - Rich Levinson, December 2017

Gabe Birnbaum reactive light project
analyzes audio, splits into 3 channels, and controls leds via pwm
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

// Create the Audio components.  These should be created in the
// order data flows, inputs/sources -> processing -> outputs
//
AudioInputI2S          audioInput;         // audio shield: mic or line-in
//AudioSynthWaveformSine sinewave;
AudioAnalyzeFFT1024    myFFT;
AudioOutputI2S         audioOutput;        // audio shield: headphones & line-out

// Connect either the live input or synthesized sine wave
AudioConnection patchCord1(audioInput, 0, myFFT, 0);
//AudioConnection patchCord1(sinewave, 0, myFFT, 0);

AudioControlSGTL5000 audioShield;

//fft range arrays
int lowBound [3] = {1, 7, 15};					//lower frequency bounds for eq channels
int highBound[3] = {6, 14, 100};				//upper frequency bounds for eq channels
//int ledPin   [9] = {0, 1, 2, 3, 4, 5, 35, 36, 37};			//led pins
int ledPin   [9] = {0, 3, 35, 1, 4, 36, 2, 5, 37};			//led pins
int ledBright [5] = {0, 15, 75, 150, 255};		//led brightness settings
int l; //number of leds for setup loop

void setup() {
  	AudioMemory(12);
  	for (l=0; l<9; l++) {		//initialize led pins
  		pinMode(ledPin[l], OUTPUT);
  	}
  	// Enable the audio shield and set the output volume.
  	audioShield.enable();
  	audioShield.inputSelect(myInput);
  	audioShield.volume(0.5);
  	// Configure the window algorithm to use
  	myFFT.windowFunction(AudioWindowHanning1024);
  	//myFFT.windowFunction(NULL);

  	// Create a synthetic sine wave, for testing
  	// To use this, edit the connections above
  	//sinewave.amplitude(0.8);
  	//sinewave.frequency(1000.007);
}

void loop() {
  float n;
  int i;	//equalizer band
  int j;	//second led for eq meter display
  int k;	//third led for eq
  int b;	//brightness for led 1
  int c;	//brightness of led 2
  int d;	//brightness of led 3

  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
	for (i=0; i<3; i++) {
		  j = i+3;		//skip to correct led in array
		  k = j+3;
	      n = myFFT.read(lowBound[i], highBound[i]);
	      if (n >= 0.01) {
			  if (n <= 0.02){
				  b = 1;	//led 1 brightness
				  c = 0;	//led 2 brightness
				  d = 0;	//led 3 brightness
			  }
			  else if (0.02 < n <= 0.03){
				  b = 2;
				  c = 0;
				  d = 0;
			  }
			  else if (0.03 < n <= 0.05){
				  b = 3;
				  c = 0;
				  d = 0;
			  }
			  else if (0.05 < n <= 0.07){
				  b = 4;
				  c = 0;
				  d = 0;
			  }
			  else if (0.07 < n <= 0.1){
				  b = 4;
				  c = 1;
				  d = 0;
			  }
			  else if (0.1 < n <= 0.14){
				  b = 4;
				  c = 2;
				  d = 0;
			  }
			  else if (0.14 < n <= 0.2){
				  b = 4;
				  c = 3;
				  d = 0;
			  }
			  else if (0.2 < n <= 0.25){
				  b = 4;
				  c = 4;
				  d = 0;
			  }
			  else if (0.25 < n <= 0.3){
				  b = 4;
				  c = 4;
				  d = 1;
			  }
			  else if (0.3 < n <= 0.4){
				  b = 4;
				  c = 4;
				  d = 2;
			  }
			  else if (0.4 < n <= 0.5){
				  b = 4;
				  c = 4;
				  d = 3;
			  }
			  else if (n > 0.5){
				  b = 4;
				  c = 4;
				  d = 4;
			  }
			  	digitalWriteFast(ledPin[i], ledBright[b]);
				digitalWriteFast(ledPin[j], ledBright[c]);
				digitalWriteFast(ledPin[k], ledBright[d]);
				Serial.print(n);
	        	Serial.print(" ");
	      } 
		  else {
			  	digitalWriteFast(ledPin[i], 0);
				digitalWriteFast(ledPin[j], 0);
				digitalWriteFast(ledPin[k], 0);
		    	Serial.print("  -  "); // don't print "0.00"
		  }
	 }
	 Serial.println();
	} 
 }



