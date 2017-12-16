// USB MIDI receive example, Note on/off -> LED on/off
// contributed by Alessandro Fasan

//set led pin
int ledPin = 2;

//function definition
int note = 1;
void OnNoteOn(byte channel, byte note, byte velocity)
{
  digitalWrite(ledPin, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(ledPin, LOW);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void loop()
{
  usbMIDI.read();
}
