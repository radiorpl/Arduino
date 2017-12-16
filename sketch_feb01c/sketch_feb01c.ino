`// Super Simple Midi Contoler

int val = 0;
int val2 = 0;

void setup()
{
   Serial.begin(31250);       // Default speed of MIDI serial port
}

void loop()
{
   val = analogRead(1)/8;      // Divide by 8 to get range of 0-127 for midi
   MIDI_TX(176,1,val);         // 176 = CC command, 1 = Which Control, val = value read from Potentionmeter
   delay(10);

   val2 = analogRead(0)/8;     // Control point 2
   MIDI_TX(176,2,val2);
   delay(10);

}

void MIDI_TX(unsigned char MESSAGE, unsigned char CONTROL, unsigned char VALUE) //pass values out through standard Midi Command
{
   Serial.print(MESSAGE);
   Serial.print(CONTROL);
   Serial.print(VALUE);
}
