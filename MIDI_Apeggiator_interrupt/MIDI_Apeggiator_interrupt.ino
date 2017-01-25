#include <MIDI.h>


volatile int pattern1 = 0;

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 7   		    // LED pin on Arduino Uno


void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  MIDI.begin();
  attachInterrupt(2, patternChange, CHANGE);
}

void loop()
{
  digitalWrite(LED,LOW);
  int time = map(analogRead(A0),0,1023,50,5000);
  int note = map(analogRead(A1),0,1023,21,108);
  //first note
  MIDI.sendNoteOn(note,127,1);
  delay(time);
  digitalWrite(LED,HIGH);		       
  MIDI.sendNoteOff(note,0,1); 
  switch (pattern1){
  case 0:
    MIDI.sendNoteOn(note+5,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+5,0,1);
    MIDI.sendNoteOn(note+8,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+8,0,1);
    break;
  case 1:
    MIDI.sendNoteOn(note+4,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+4,0,1);
    MIDI.sendNoteOn(note+8,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+8,0,1);
    break;
  case 2:
    MIDI.sendNoteOn(note+6,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+6,0,1);
    MIDI.sendNoteOn(note+8,127,1);
    delay(time);		       
    MIDI.sendNoteOff(note+8,0,1);
  }
  //last note
  MIDI.sendNoteOn(note+12,127,1);
  delay(time);		       
  MIDI.sendNoteOff(note+12,0,1);

}

void patternChange()
{
  pattern1++;// = (pattern1+1)%3;
}



