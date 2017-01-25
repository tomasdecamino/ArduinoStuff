/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include "Mouse.h"

#define SENS 2

void setup() {
  // put your setup code here, to run once:
  Mouse.begin();
  CircuitPlayground.begin();
}

void loop() {
  // lee el acelerometro
  // SENS determina la sensibilidad al movimiento
  int mX = CircuitPlayground.motionX() / SENS;
  int mY = CircuitPlayground.motionY() / SENS;
  //usa medida ecelerometro para mover mouse
  Mouse.move(mX, mY, 0);
  //boton del mouse es el boton del CP
  if (CircuitPlayground.leftButton()) {
    Mouse.press(MOUSE_LEFT);
  } else {
    Mouse.release(MOUSE_LEFT);
  }
}
