/*Tomas de Camino Beck
  www.funcostarica.org
  Medidor de pulsos
  Released under MIT License
  Copyright (c) 2016 Tomas de-Camino-Beck
*/
#include <Adafruit_CircuitPlayground.h>


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(1, CircuitPlayground.strip.Color(0, 255, 0));
}

void loop() {
  int pulse = CircuitPlayground.lightSensor();
  int color = map(pulse,80,190,0,255);
  CircuitPlayground.setPixelColor(5, CircuitPlayground.strip.Color(color, 0, 0));
  delay(10);
}


