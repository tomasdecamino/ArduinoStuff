/*Tomas de Camino Beck
  www.funcostarica.org
  Simple medidor de impacto
  Released under MIT License
  Copyright (c) 2016 Tomas de-Camino-Beck
*/
#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>

Servo servo1, servo2;


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  servo1.attach(12);
  servo2.attach(6);
}


void loop() {
  servo1.write(60);
  servo2.write(60);
}



