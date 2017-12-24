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
	//int pwm = map(n, 0.0, 1.0, 0, 255);
	
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
	//int m = n * 100;
	//int pwm = map(m, 0, 100, 0, 255);

 	if (fft1024_1.available()) {
	    // each time new FFT data is available
	    // print it all to the Arduino Serial Monitor
	    Serial.print("FFT: ");
		for (i=0; i<3; i++) {
			  j = i+3;		//skip to correct led in array
			  k = j+3;
		      n = fft1024_1.read(lowBound[i], highBound[i]);
		  	//int m = n * 100;
		  	//int m = map(n, 0.0, 0.6, 0, 10);  //map levels to 10 steps
			//constrain(m, 0, 10);	
			int pwm = map(n, 0.0, 0.85, 0, 255);  //map steps
			constrain(pwm, 0, 255);		//constrain to pwm range
			int pwm_follower = pwm - 100;  		//follower pwm for next strip
			if (pwm_follower < 0){
				pwm_follower = 0;
			}
			int last_pwm; 
		      	if (n >= 0.03){
				  	if (n <= 0.2){
					 	if (abs(last_pwm - pwm) < 10){
   					 		b = pwm;
   					  		c = pwm_follower;
   					  		d = 0;
						}
						else {
						
					}
				  }
				  else if (0.2 < n && n <= 0.5){
					  b = 255;
					  c = pwm;
					  d = pwm_follower;
				  }
				  else if (n > 0.5){
					  b = 255;
					  c = 255;
					  d = pwm;
				  }
				  	analogWrite(ledPin[i], b);
					analogWrite(ledPin[j], c);
					analogWrite(ledPin[k], d);
					Serial.print(pwm);
		        	Serial.print(" ");
					last_pwm = pwm;
					//delay(10);
		      } 
			  else {
				  	analogWrite(ledPin[i], ledBright[0]);
					analogWrite(ledPin[j], ledBright[0]);
					analogWrite(ledPin[k], ledBright[0]);
			    	Serial.print("  -  "); // don't print "0.00"
			  }
		 }
		 Serial.println();
		} 
 }
