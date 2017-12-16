//PIN's definition
#define encoder0PinA  22
#define encoder0PinB  23


volatile int encoder0Pos = 0;
volatile boolean PastA = 0;
volatile boolean PastB = 0;

void setup()
{ Serial.begin(9600);
  pinMode(encoder0PinA, INPUT);
  //turn on pullup resistor
  //digitalWrite(encoder0PinA, HIGH); //ONLY FOR SOME ENCODER(MAGNETIC)!!!!
  pinMode(encoder0PinB, INPUT);
  //turn on pullup resistor
  //digitalWrite(encoder0PinB, HIGH); //ONLY FOR SOME ENCODER(MAGNETIC)!!!!
  PastA = (boolean)digitalRead(encoder0PinA); //initial value of channel A;
  PastB = (boolean)digitalRead(encoder0PinB); //and channel B

  //To speed up even more, you may define manually the ISRs
  // encoder A channel on interrupt 0 (Arduino's pin 2)
  attachInterrupt(0, doEncoderA, RISING);
  // encoder B channel pin on interrupt 1 (Arduino's pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);
}


void loop()
{
  //your stuff....ENJOY! :D
}

//you may easily modify the code get quadrature..
//..but be sure this wouldn't let Arduino back!
void doEncoderA()
{
  PastB ? encoder0Pos-- :  encoder0Pos++;
  Serial.print("read");
}

void doEncoderB()
{
  PastB = !PastB;
}

