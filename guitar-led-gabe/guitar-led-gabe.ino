/*
Sketch to control led with pwm, controlled by audio input
to get audio signal in, need voltage divider, see http://interface.khm.de/index.php/lab/interfaces-advanced/arduino-realtime-audio-processing/ for
schematic, specifically voltage divider on analog input. 

Use 10uF coupling cap into 100k resistor voltage diver with 10k pot going from signal to V+ resistor in the divider. Signal also coupled to 
ground using .0047 cap or the like
*/
const int ledPin =  5;
int midValue = 466;

void setup(){
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
}

void loop(){
	int guitValue = analogRead(A0);
	Serial.println(guitValue);	
	if (abs(guitValue - midValue) < 10) {
		analogWrite(ledPin, 0);
	}
	else if (9 < (abs(guitValue - midValue)) < 15) {
		analogWrite(ledPin, 15);
	}
	else if (14 < (abs(guitValue - midValue)) < 20) {
		analogWrite(ledPin, 30);
	}
	else if (19 < (abs(guitValue - midValue)) < 25) {
		analogWrite(ledPin, 45);
	}
	else if (24 < (abs(guitValue - midValue)) < 30) {
		analogWrite(ledPin, 60);
	}
	else if (29 < (abs(guitValue - midValue)) < 35) {
		analogWrite(ledPin, 75);
	}
	else if (34 < (abs(guitValue - midValue)) < 40) {
		analogWrite(ledPin, 90);
	}
	else if (39 < (abs(guitValue - midValue)) < 45) {
		analogWrite(ledPin, 105);
	}
	else if (44 < (abs(guitValue - midValue)) < 50) {
		analogWrite(ledPin, 120);
	}
	else if (49 < (abs(guitValue - midValue)) < 55) {
		analogWrite(ledPin, 135);
	}
	else if (54 < (abs(guitValue - midValue)) < 60) {
		analogWrite(ledPin, 150);
	}
	else if (59 < (abs(guitValue - midValue)) < 65) {
		analogWrite(ledPin, 165);
	}
	else if (64 < (abs(guitValue - midValue)) < 70) {
		analogWrite(ledPin, 180);
	}
	else if (69 < (abs(guitValue - midValue)) < 75) {
		analogWrite(ledPin, 195);
	}
	else if (74 < (abs(guitValue - midValue)) < 80) {
		analogWrite(ledPin, 210);
	}
	else if (79 < (abs(guitValue - midValue)) < 85) {
		analogWrite(ledPin, 225);
	}
	else if ((abs(guitValue - midValue)) > 84) {
		analogWrite(ledPin, 255);
	}
	//analogWrite(ledPin, guitValue);
	//delay(5);
}
  