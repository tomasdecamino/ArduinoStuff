/*Tomas de Camino Beck
  www.funcostarica.org
  Learning colors
  Released under MIT License
  Copyright (c) 2016 Tomas de-Camino-Beck
*/

#include "Adafruit_CircuitPlayground.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "keys.h"

#define SENSE 100


void setup() {
  CircuitPlayground.begin();
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  if (CircuitPlayground.slideSwitch()) {

    // put your main code here, to run repeatedly:
    // Serial.println(CircuitPlayground.readCap(10));
    (CircuitPlayground.readCap(10) > SENSE) ? sendKey(10) : false;
    (CircuitPlayground.readCap(9) > SENSE) ? sendKey(9) : false;
    (CircuitPlayground.readCap(6) > SENSE) ? sendKey(6) : false;
    (CircuitPlayground.readCap(12) > SENSE) ? sendKey(12) : false;
    (CircuitPlayground.readCap(3) > SENSE) ? sendKey(3) : false;
    (CircuitPlayground.readCap(2) > SENSE) ? sendKey(2) : false;
    (CircuitPlayground.readCap(0) > SENSE) ? sendKey(0) : false;
    (CircuitPlayground.readCap(1) > SENSE) ? sendKey(1) : false;

   //mouse movement
   float dX=CircuitPlayground.motionX();
   float dY=CircuitPlayground.motionY();
   Mouse.move(-dY,dX);
   if(CircuitPlayground.leftButton()) Mouse.click(MOUSE_LEFT);
   if(CircuitPlayground.rightButton()) Mouse.click(MOUSE_RIGHT);
  }

}


boolean sendKey(byte pad) {
  switch (pad) {
    case 10:
      Keyboard.write(KEY10);
      CircuitPlayground.setPixelColor(8, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 9:
      Keyboard.write(KEY9);
      CircuitPlayground.setPixelColor(8, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 6:
      Keyboard.write(KEY6);
      CircuitPlayground.setPixelColor(6, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 12:
      Keyboard.write(KEY12);
      CircuitPlayground.setPixelColor(6, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 3:
      Keyboard.write(KEY3);
      CircuitPlayground.setPixelColor(1, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 2:
      Keyboard.write(KEY2);
      CircuitPlayground.setPixelColor(1, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 0:
      Keyboard.write(KEY0);
      CircuitPlayground.setPixelColor(3, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    case 1:
      Keyboard.write(KEY1);
      CircuitPlayground.setPixelColor(3, CircuitPlayground.strip.Color(255, 0, 0));
      delay(10);
      break;
    default:
      CircuitPlayground.clearPixels();
      break;
  }
  CircuitPlayground.clearPixels();
}


