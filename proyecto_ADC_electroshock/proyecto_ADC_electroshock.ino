
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

long firstMillis = millis();
int time;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  time =30;
  firstMillis = millis();
  pinMode(9,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);  
  digitalWrite(9,LOW);
}

void loop() {
  // try to print a number thats too long
  int newSecs = (millis()-firstMillis)/1000;
  if(newSecs>=30){
    firstMillis = millis();
  }
  if(digitalRead(7)==LOW){
    firstMillis = millis();
  }
  Serial.println((time-newSecs)-(10*floor((time-newSecs)/10)));
  matrix.writeDigitNum(0, (time-newSecs)/10, false);
  matrix.writeDigitNum(1,(time-newSecs)-(10*floor((time-newSecs)/10)), false);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, 0, false);
  matrix.writeDigitNum(4, 0, false);
  matrix.writeDisplay();
  if((digitalRead(2)==LOW)||(digitalRead(3)==LOW)||(digitalRead(4)==LOW)){
    digitalWrite(9,HIGH);
  }else{
    digitalWrite(9,LOW);
  }
  if(newSecs)
  delay(5);

}

