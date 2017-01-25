#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_LSM303.h>


Adafruit_LSM303 lsm;

volatile int state = LOW;
int note=42;

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();


void setup()
{
  lsm.begin();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7,HIGH);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  MIDI.begin(1);
  attachInterrupt(0, turnOn, RISING);
}

void loop()
{
  lsm.read();
  int time = map(analogRead(A0),0,1023,50,1000);
  int velocity =127;
  int arp = map(analogRead(A1),0,1023,1,27);
  int note= map(lsm.accelData.x,-1100,1100,108,21);
  //int note= map(analogRead(A2),0,1023,108,21);
 /* if(MIDI.read()){
    digitalWrite(7,LOW);
    note=MIDI.getData1();
    digitalWrite(7,HIGH);
  }*/
  if(state){
    digitalWrite(6,HIGH);
    MIDI.sendNoteOn(note,velocity,1);
    delay(time);		       
    MIDI.sendNoteOff(note,0,1);   
    MIDI.sendNoteOn(note+arp,velocity,1);
    delay(time);		       
    MIDI.sendNoteOff(note+arp,0,1);
    MIDI.sendNoteOn(note+8,velocity,1);
    delay(time);		       
    MIDI.sendNoteOff(note+8,0,1);
    MIDI.sendNoteOn(note+12,velocity,1);
    delay(time);		       
    MIDI.sendNoteOff(note+12,0,1);
  }
  digitalWrite(6,LOW);
}

void turnOn()
{
  state = !state;
}


