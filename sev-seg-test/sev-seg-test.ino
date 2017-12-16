/*
 Works for spelling butt on 7 segment display
 From http://sainsb.github.io/2012/04/28/the-teensy-and-the-4-digit-7-segment-display/
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

//Segment pins 
int ledPins[] = {2, 14, 7, 8, 6, 20, 21, 5};
int pinCount = 8;
//Dig pins 
int digPins[] = {9, 10, 11, 12};
int pinCountDig = 4;
int digit0 = 9; 


elapsedMillis m_blinkTime; // Blink timer for the LED

//====setup=====

void setup() {

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

//blink led pin 13 function
void BlinkLED() {
  if (m_blinkTime < 250) {
    digitalWrite(13, LOW);
  } else if (m_blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    m_blinkTime = 0; // start blink cycle over again
  }
}

//==main loop====

void loop()
{
 // BlinkLED();
  
  // light up first digit only
  digitalWriteFast(digPins[0],HIGH);
  digitalWriteFast(digPins[1],LOW);
  digitalWriteFast(digPins[2],LOW);
  digitalWriteFast(digPins[3],LOW);
    // light up segments of first digit, display number #1, segments bc
    GPIOD_PDOR=B10000000; //B00011000; // only pins 2 and 3 are on
  //digitalWrite(8,HIGH); // turn off pin 8
delay(2);
  // light up second digit only
  digitalWriteFast(digPins[0],LOW);
  digitalWriteFast(digPins[1],HIGH);
  digitalWriteFast(digPins[2],LOW);
  digitalWriteFast(digPins[3],LOW);
    // light up segments of first digit, display number #1, segments bc
    GPIOD_PDOR=B11000001; //B00011000; // only pins 2 and 3 are on
  //digitalWrite(8,HIGH); // turn off pin 8
delay(2);
  // light up third digit only
  digitalWriteFast(digPins[0],LOW);
  digitalWriteFast(digPins[1],LOW);
  digitalWriteFast(digPins[2],HIGH);
  digitalWriteFast(digPins[3],LOW);
    // light up segments of first digit, display number #1, segments bc
    GPIOD_PDOR=B10000111; //B00011000; // only pins 2 and 3 are on
  //digitalWrite(8,HIGH); // turn off pin 8
delay(2);
  // light up fourth digit only
  digitalWriteFast(digPins[0],LOW);
  digitalWriteFast(digPins[1],LOW);
  digitalWriteFast(digPins[2],LOW);
  digitalWriteFast(digPins[3],HIGH);
    // light up segments of first digit, display number #1, segments bc
    GPIOD_PDOR=B10000111; //B00011000; // only pins 2 and 3 are on
  //digitalWrite(8,HIGH); // turn off pin 8
delay(2);
}
/*
  // light up second digit only
  digitalWrite(d1,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);
  digitalWrite(d2,HIGH);
    // light up segments of second digit, display #2, segments abdeg
    PORTD=B10010011; //B01101100; // only pins 2,3,5 and 6 on
    digitalWrite(8,LOW); // segment g on
delay(2);
  // light up third digit only
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d4,LOW);
  digitalWrite(d3,HIGH);
    // light up segments of third digit, display #3
    PORTD=B11000011; //B00111100; // only pins 2,3 and 5 on
    digitalWrite(8,LOW); // segment g on
delay(2);
  // light up fourth digit only
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,HIGH);
    // light up segments of fourth digit only, display #4
    PORTD=B01100111; //B10011000; // only pins 3,4 and 7 on
    digitalWrite(8,LOW); // segment g on
delay(2);
}

/*
void loop(){
  //pinMode(9,LOW);
  //GPIOD_PDOR=0x;
  
  BlinkLED();
  
  //GPIOD_PDOR = B00000011;
  
  do {
  for (int i=0; i<=7; i++)
  {
  byte b = 1<<i;
  digitalWriteFast(12, HIGH);
  Serial.println(ledPins[i]);
  delay(1000);
  }
  } 
  while (1==1);
}


 
/*
int perDigitTime = 100;
int digitPosition = 1;  
unsigned long previousMillis = 0;

int value = 0;
int powerOfTen[] = {1,10,100,1000};

void RefreshDisplay() {
  digitalWrite(digit0 + digitPosition, LOW);
  digitPosition++;
  if (digitPosition > 3) digitPosition = 0;

  int digitValue = value % powerOfTen[ digitPosition+1 ] / powerOfTen[digitPosition];
  int number =  numbers[ digitValue ];

  if ((number > 0) || (value < powerOfTen[ digitPosition+1 ]))
  {
  GPIOD_PDOR=number;
  digitalWrite(digit0 + digitPosition, HIGH);
  delay(4);
  }
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > perDigitTime)
  {
    previousMillis = currentMillis;
    value++;
  }

  RefreshDisplay();

}
*/
