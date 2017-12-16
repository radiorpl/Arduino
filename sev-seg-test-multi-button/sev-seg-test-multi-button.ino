/*
 Sketch counts button clicks, and changes 7 segment display in sequence
 Edit 7/7/17 - check button function working 
 Edit7/5/17 function to turn on leds and take character argument
 Works for spelling butt on 7 segment display 7/3/17
 From http://sainsb.github.io/2012/04/28/the-teensy-and-the-4-digit-7-segment-display/
 For use with common Anode 4-digit 7 Segment display
 My seven seg display info:
 W I R I N G   G U I D E


=== Common Cathode digits ===
Arduino  Display  Digit
 9         12       0 Leftmost
 10         9       1
 11         8       2
 12         6       3 Rightmost
 
=== Anode Segments ===
Teensy    GPIOD    Display   Segment  
  2        0        11         A
  14       1        7          B
  7        2        4          C
  8        3        2          D
  6        4        1          E
  20       5        10         F
  21       6        5          G
  5        7        3         DEC  

===Segment Layout===
    A
  F   B
    G
  E   C
    D   
          byte .GFEDCBA
segment code, Bxxxxxxxx
*/  
//Define Sev seg pins and make function to DigitalWriteFast all pins at once https://programmingelectronics.com/tutorial-13-how-to-use-arrays-with-arduino/
// outputs pins for segments


//====Variables======
//Segment pins 
byte segPins[] = {2, 14, 7, 8, 6, 20, 21, 5}; //segments
byte pinCountSeg = 8;               //segment led count
byte digPins[] = {9, 10, 11, 12};   //digit pins
byte pinCountDig = 4;         //number of digits
byte digit0 = 9;              //first digit pin
byte buttonPins[] = {1, 3};     // the numbers of the pushbutton pins
byte buttonCount = 2;         //number of buttons
int buttonPushCounter[] = {0, 0};   // counter for the number of button presses       
int buttonState [] = {};      // current state of the buttons
int lastButtonState[] = {0,0};     // previous state of the buttons
//int buttonPin = 0;
//===numbers and letters for 7 digit display
byte numberLetter[] = {     
  B11000000, // 0
  B11111001, // 1
  B10100100, // 2
  B10110000, // 3
  B10011001, // 4
  B10010010, // 5
  B10000010, // 6
  B11111000, // 7
  B10000000, // 8
  B10010000,  // 9
  B10001000, // 10 A
  B10000011, // 11 b
  B11000110, // 12 C
  B10100001, // 13 d
  B10000110, // 14 E
  B10001110, // 15 F
  B10010000, // 16 g
  B10001001, // 17 H
  B11001111, // 18 I
  B11000001, // 19 J
  B10001001, // 20 K = H
  B11000111, // 21 L
  B11101010, // 22 m
  B10101011, // 23 n
  B11000000, // 24 O = 0
  B10001100, // 25 P
  B10011000, // 26 q
  B10101111, // 27 r
  B10010010, // 28 S
  B10000111, // 29 t
  B11000001, // 30 U
  B11100011, // 31 v
  B11010101, // 32 w
  B10001001, // 33 X = H
  B10010001, // 34 y
  B10100100,  // 35 Z = 2
  B11111111  // 36 all off      
};

elapsedMillis m_blinkTime; // Blink timer for the LED

//====Main Sketch=====

//====setup=====

void setup() {
  Serial.begin(9600);
  GPIOD_PDDR=0xff;
  GPIOD_PDOR=0x00;
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each segment pin as an output:
  for (int pinSeg = 0; pinSeg < pinCountSeg; pinSeg++) {
    pinMode(segPins[pinSeg], OUTPUT);
  }
  for (int pinDig = 0; pinDig < pinCountDig; pinDig++) {    // set digit pins as outputs
    pinMode(digPins[pinDig], OUTPUT);
  } 
  for (int PinButton = 0; PinButton < buttonCount; PinButton++) {     //set up button pins as inputs
    pinMode(buttonPins[PinButton], INPUT); 
  }  
}



//====Functions=====
/*
//blink led pin 13 function
void BlinkLED() {
  if (m_blinkTime < 250) {
    digitalWrite(13, LOW);
  }
  else if (m_blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    m_blinkTime = 0; // start blink cycle over again
  }
}
*/
//Turn on digits, wait 2ms, go to next
void digitOn(int digit, int character){
  if (digit == 0){
    digitalWriteFast(digPins[0],HIGH); //first digit on
    digitalWriteFast(digPins[1],LOW); //other pins off
    digitalWriteFast(digPins[2],LOW);
    digitalWriteFast(digPins[3],LOW);
    GPIOD_PDOR=numberLetter[character]; //set character
    delay(2);
 }
  else if (digit == 1) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],HIGH); //second digit on
    digitalWriteFast(digPins[2],LOW);
    digitalWriteFast(digPins[3],LOW);
    GPIOD_PDOR=numberLetter[character]; //set character
    //Serial.println(digit);
    delay(2);
  }
  else if (digit == 2) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],LOW); 
    digitalWriteFast(digPins[2],HIGH); //third digit on 
    digitalWriteFast(digPins[3],LOW);
    GPIOD_PDOR=numberLetter[character]; //set character
    delay(2);
  }  
  else if (digit == 3) {
    digitalWriteFast(digPins[0],LOW); //other pins off
    digitalWriteFast(digPins[1],LOW); 
    digitalWriteFast(digPins[2],LOW);  
    digitalWriteFast(digPins[3],HIGH); //Fourth digit on
    GPIOD_PDOR=numberLetter[character]; //set character
    delay(2);
  }
}
//==========button function
  
    void checkButton(int pinButton){
    //pinButton = position in buttonPins array + all the other arrays that store data for the buttons
    for (int pinButton = 0; pinButton < buttonCount; pinButton++) {          
    // read the pushbutton input pin
    buttonState[pinButton] = digitalRead(buttonPins[pinButton]);     
    // compare the buttonState to its previous state, if the state has changed, increment the counter
    if (buttonState[pinButton] != lastButtonState[pinButton] && buttonState[pinButton] == HIGH) {                                    
    // if the current state is HIGH then the button send from off to on:
    buttonPushCounter[pinButton]++;                               
    Serial.println("on");
    Serial.print("number of button pushes:  ");
    Serial.println(buttonPushCounter[pinButton]);
    Serial.println(pinButton);
    } 
    //else {Serial.println("off");}      // if the current state is LOW then the button send from on to off  
    lastButtonState[pinButton] = buttonState[pinButton];   // save the current state as the last state, for next time through the loop
  }
}


  


//====Main Loop======
void loop() {
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  
  //check buttons
  checkButton(0);
  checkButton(1);
  
  //states
  if (buttonPushCounter[0] == 0) {
  // write 'home'
  digitOn(0,17);
  digitOn(1,24);
  digitOn(2,22);
  digitOn(3,14);
  //Serial.println(buttonPushCounter);   
  } 
  else if (buttonPushCounter[0] % 2 == 1) {
  //write 'one'
  digitOn(0,24);
  digitOn(1,23);
  digitOn(2,14);
  digitOn(3,36);
  //Serial.println(buttonPushCounter);
  }
  else if (buttonPushCounter[0] % 2 == 0){
  //write 'two2'
  digitOn(0,29);
  digitOn(1,32);
  digitOn(2,24);
  digitOn(3,2);
  //Serial.println(buttonPushCounter[pinButton]);
  } 
}


