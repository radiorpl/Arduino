// FFT Test
//
// Compute a 1024 point Fast Fourier Transform (spectrum analysis)
// on audio connected to the Left Line-In pin.  By changing code,
// a synthetic sine wave can be input instead.
//
// The first 40 (of 512) frequency analysis bins are printed to
// the Arduino Serial Monitor.  Viewing the raw data can help you
// understand how the FFT works and what results to expect when
// using the data to control LEDs, motors, or other fun things!
//
// This example code is in the public domain.

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
AudioSynthWaveformSine sinewave;
AudioAnalyzeFFT1024    myFFT;
AudioOutputI2S         audioOutput;        // audio shield: headphones & line-out

// Connect either the live input or synthesized sine wave
AudioConnection patchCord1(audioInput, 0, myFFT, 0);
//AudioConnection patchCord1(sinewave, 0, myFFT, 0);

AudioControlSGTL5000 audioShield;

//fft range arrays
int lowBound [3] = {1, 7, 15};
int highBound[3] = {6, 14, 110};
int ledPin   [6] = {0, 1, 2, 3, 4, 5};
int ledBright [5] = {0, 30, 100, 175, 255};
int l; //number of leds for setup loop

void setup() {
  	// Audio connections require memory to work.  For more
  	// detailed information, see the MemoryAndCpuUsage example
  	AudioMemory(12);
  	for (l=0; l<6; l++) {
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
  	sinewave.amplitude(0.8);
  	sinewave.frequency(1000.007);
}

void loop() {
  float n;
  int i;	//equalizer band
  int j;	//second led for eq meter display
  int b;	//brightness for led 1
  int c;	//brightness of led 2

  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
	for (i=0; i<3; i++) {
		  j = i+3;
	      n = myFFT.read(lowBound[i], highBound[i]);
	      if (n >= 0.01) {
			  if (n <= 0.02){
				  b = 1;
				  c = 0;
			  }
			  else if (0.02 < n <= 0.03){
				  b = 2;
				  c = 0;
			  }
			  else if (0.03 < n <= 0.05){
				  b = 3;
				  c = 0;
			  }
			  else if (0.05 < n <= 0.07){
				  b = 4;
				  c = 0;
			  }
			  else if (0.07 < n <= 0.1){
				  b = 4;
				  c = 1;
			  }
			  else if (0.1 < n <= 0.14){
				  b = 4;
				  c = 2;
			  }
			  else if (0.14 < n <= 0.2){
				  b = 4;
				  c = 3;
			  }
			  else if (n > 0.20){
				  b = 4;
				  c = 4;
			  }
			  	digitalWriteFast(ledPin[i], ledBright[b]);
				//digitalWriteFast(ledPin[j], 0);
				digitalWriteFast(ledPin[j], ledBright[c]);
				Serial.print(n);
	        	Serial.print(" ");
	      } 
		  else {
			  	digitalWriteFast(ledPin[i], 0);
				digitalWriteFast(ledPin[j], 0);
		    	Serial.print("  -  "); // don't print "0.00"
		  }
	 }
	 Serial.println();
	} 
 }



