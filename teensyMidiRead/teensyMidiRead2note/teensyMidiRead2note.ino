// USB MIDI receive example, Note on/off -> LED on/off
// contributed by Alessandro Fasan

//set led pin
int ledPin = 2;
int ledPina = 3;

//function definition
void OnNoteOn(byte channel, byte note, byte velocity)
{
  if (note == 0) {
  digitalWrite(ledPin, HIGH);
 }
  else if (note == 1) {
  digitalWrite(ledPina, HIGH);
 }
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  if (note == 0) {
  digitalWrite(ledPin, LOW);
 }
  else if (note == 1) {
  digitalWrite(ledPina, LOW);
 }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ledPina, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPina, HIGH);
  delay(500);
  digitalWrite(ledPina, LOW);
  delay(500);
}

void loop()
{
  usbMIDI.read();
}
