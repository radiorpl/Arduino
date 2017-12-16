/*
PTx Power Appearance Model Sketch
10/7/15
Rich Levinson

When button is pressed, LED array turns on with 100 ms between LEDs, stays on for 
2 seconds, then turns off at once

Button has 10K pullup resistor
 
*/

// constants won't change. They're used here to 
// set pin numbers:
//int timer = 100;            // delay between LEDs turning on
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPins[] = {
  5, 6, 7, 8, 9
};                          // an array of pin numbers to which LEDs are attached
int pinCount = 5;           // the number of pins (i.e. the length of the array)

int buttonState = 0;        // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
 
  for (int i = 0; i < 5; i++)
{
  pinMode(ledPins[i], OUTPUT);  
}  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT); 
  Serial.begin(9600);
  Serial.print("PTx Blinker");  
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (buttonState == LOW) {     
    // turn LEDs on:    
   int delayTime = 100; //the time (in milliseconds) to pause between LEDs
                          //make smaller for quicker switching and larger for slower'
     for (int i = 0; i < 5; i++)
     {
       digitalWrite(ledPins[i], HIGH);
       delay(delayTime);
     }
     delay(2000);
     for (int i = 0; i < 5; i++)
     {
       digitalWrite(ledPins[i], LOW);
     }      
  } 
  else {
    // turn LED off:
     for (int i = 0; i < 5; i++)
     {
       digitalWrite(ledPins[i], LOW);
     }      
  }
}
