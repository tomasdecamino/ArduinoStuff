/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

//cambiar el tiempo para duración
#define TIME 10 //tiempo en segundos

long lastMillis;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  lastMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (millis() - lastMillis < (TIME * 1000)) {
    int rnd =  random(10);
    CircuitPlayground.setPixelColor(rnd, CircuitPlayground.strip.Color(200, 150, 0));
    CircuitPlayground.playTone(500, 200);
    delay(200);
    CircuitPlayground.clearPixels();

  }

  for (int i = 0; i <= 11; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255, 0, 0));
  }
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  if (CircuitPlayground.leftButton()) {
    lastMillis = millis();
  }
}
