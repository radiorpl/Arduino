/*
 WAS: Testing SparkFun's 4-digit 7-Segment Display (Blue)
 NOW: Altered for GmDude66 for H.LTC.4727
*/

int segmentA = 0; // Segments A thru P == pins 0 thru 7
int digit0 = 8; // Digits 3 thru 0 == pins 10 thru 13 (0 is LEFT most digit)

/*
[glow]Change#1 Added wiring guide for your H.LTC.4727[/glow]

W I R I N G   G U I D E

=== Common Cathode digits ===
Arduino  Display  Digit
 8        12       0 Leftmost
 9        9       1
 10        8       2
 11        6       3 Rightmost
 
=== Anode Segments ===
Arduino  Display   Segment
  0       11         A
  1       7         B
  2       4         C
  3       2          D
  4       1          E
  5       10         F
  6       5         G
  7      3     DEC         
*/

/*
10 digits:
Each defines which segments should be on/off for that digit: A,B,C,D,E,F,G,P
*/
byte numbers[10] =
{
 B11000000, // 0
 B11111001, // 1
 B10100100, // 2
 B10110000, // 3
 B10011001, // 4
 B10010010, // 5
 B10000010, // 6
 B11111000, // 7
 B10000000, // 8
 B10010000  // 9
};

void setup()
{
 for (byte segment = 0; segment < 8; segment++)
   pinMode(segmentA+segment,OUTPUT);

 for (byte digit = 0; digit < 4; digit++)
   pinMode(digit0+digit,OUTPUT);
}

int perDigitTime = 100;
int digitPosition = 1;  // Start anywhere but zero so we won't crash when we try to turn off previous digit.
unsigned long previousMillis = 0;

int value = 0;
int powerOfTen[] = {
 1,10,100,1000};

void RefreshDisplay()
{
[glow]  //Change#2 (Your display is common Cathode, so to turn OFF a digit, we need to set it to +5)[/glow]
 digitalWrite(digit0 + digitPosition, [glow]HIGH[/glow]);  // Turn off previous digit

 digitPosition++;
 if (digitPosition > 3) digitPosition = 0;

 int digitValue = value % powerOfTen[ digitPosition+1 ] / powerOfTen[digitPosition];
 int number =  numbers[ digitValue ];
 
 if ((number > 0) || (value < powerOfTen[ digitPosition+1 ]))
 {
 for (byte seg = 0; seg < 8; seg++)
   digitalWrite(segmentA+seg, [glow]1 - [/glow]bitRead(number, seg) ); [glow]// Change#3 added "1-" to invert the bit for your common Cathode display[/glow]

 digitalWrite(digit0 + digitPosition, [glow]LOW[/glow]);  [glow]//Change#4 LOW will turn this digit on.[/glow]
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
