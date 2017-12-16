/*
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
byte ledPins[] = {2, 14, 7, 8, 6, 20, 21, 5};
byte pinCount = 8;
//Dig pins 
byte digPins[] = {9, 10, 11, 12};
byte pinCountDig = 4;
byte digit0 = 9; 

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

char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";  // last element is blank

elapsedMillis m_blinkTime; // Blink timer for the LED

//====Main Sketch=====

//====setup=====

void setup() {
  Serial.begin(9600);
  GPIOD_PDDR=0xff;
  GPIOD_PDOR=0x00;
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  // same for dig pins
  for (int thisPinDig = 0; thisPinDig < pinCountDig; thisPinDig++) {
    pinMode(digPins[thisPinDig], OUTPUT);
  //pin 13 led  
    pinMode(13, OUTPUT);
  }
}

//====Functions=====

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
//character translation
void charTranslate(char letter){
  for (int i = 0; i<37; i++) 
  alphabet[i]=numberLetter[i];
  
  }


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




//====Main Loop======
void loop() {
  Serial.println(numberLetter[10]);
  digitOn(0,10);
  digitOn(1,2);
  digitOn(2,3);
  digitOn(3,4);
}


