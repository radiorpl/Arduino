const int  buttonPin = 3;      //non atm button
byte buttonPushCounter = 0;
byte buttonState = 0;
byte lastButtonState = 0;
byte encSwitch;  //determines which instance encoder controls


void setup() {
  Serial.begin( 9600 );
  pinMode(buttonPin, INPUT);
  //digitalWrite(buttonPin, LOW);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  /*
  if (buttonPushCounter > 1 ){
    buttonPushCounter = 0;
  }
  encSwitch = buttonPushCounter;
  Serial.print("encSwitch = ");
  Serial.println(encSwitch);
  
*/
}
