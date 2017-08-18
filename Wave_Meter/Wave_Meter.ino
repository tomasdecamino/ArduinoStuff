
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

byte count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address
}



void loop() {

 // int val = map(analogRead(A0), 0, 50, 0, 8);
//  Serial.println(val);
  matrix.clear();      // clear display
  for (int j = 0; j < 7; j++) {
    int val = constrain(map(analogRead(A0), 0, 10, 0, 8),0,7);
    for (int i = 0; i < val; i++)
      matrix.drawPixel(j, 8-i, LED_ON);
    matrix.writeDisplay();  // write the changes we just made to the display
    count = (count + 1) % 8;
  }
  delay(100);

  //matrix.setRotation(0);
}
