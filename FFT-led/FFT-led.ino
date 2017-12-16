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
int lowBound [6] = {0, 5, 11, 21, 41, 71};
int highBound[6] = {4, 10, 20, 40, 70, 110};
int ledPin   [6] = {4, 5, 8, 16, 17, 20};
int ledBright [6] = {15, 30, 60, 120, 240, 255};
int l;

void setup() {
  	// Audio connections require memory to work.  For more
  	// detailed information, see the MemoryAndCpuUsage example
  	AudioMemory(12);
  	for (l=0; l<5; l++) {
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
  int i;

  if (myFFT.available()) {
    // each time new FFT data is available
    // print it all to the Arduino Serial Monitor
    Serial.print("FFT: ");
	for (i=0; i<6; i++) {
	      n = myFFT.read(lowBound[i], highBound[i]);
	      if (n >= 0.01) {
			  	digitalWriteFast(ledPin[i], 255);
				Serial.print(n);
	        	Serial.print(" ");
	      } 
		  else {
			  	digitalWriteFast(ledPin[i], 0);
		    	Serial.print("  -  "); // don't print "0.00"
		  }
	 }
	 Serial.println();
	} 
 }


