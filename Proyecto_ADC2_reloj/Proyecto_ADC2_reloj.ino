
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Time.h>  

int count =0;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  setTime(0,0,0,1,1,2001);
  matrix.writeDigitNum(0, 0, false);
  matrix.writeDigitNum(1, 0, false);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, 0, false);
  matrix.writeDigitNum(4, 0, false);
  matrix.writeDisplay();
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  // method #2 - draw each digit
  while(count==0){
    count+=digitalRead(2)==LOW;
    setTime(0,0,0,1,1,2001); 
  }
  matrix.writeDigitNum(0, 0, false);
  matrix.writeDigitNum(1, minute(), false);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, second()/10 , false);
  matrix.writeDigitNum(4, second()%10, false);
  matrix.writeDisplay();
  count+=digitalRead(2)==LOW; 
  if((digitalRead(3)==LOW) ||minute()==2){
    count=0;
    matrix.writeDigitNum(0, 0, false);
    matrix.writeDigitNum(1, 0, false);
    matrix.drawColon(true);
    matrix.writeDigitNum(3, 0 , false);
    matrix.writeDigitNum(4, 0, false);
    matrix.writeDisplay();
    delay(500);
  }
}



