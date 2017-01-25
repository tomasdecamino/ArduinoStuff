/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

int nota, notaAnterior;//para saber si el pie se mueve

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  notaAnterior = nota;
  //detecta el valor del acelerometro
  nota = map(CircuitPlayground.motionX(), -10, 10, 50, 800);
  //si es diferente del valor anterior entonces suena
  if (abs(nota - notaAnterior) > 2) {

    CircuitPlayground.playTone(nota, 100);
    delay(100);
    for (int i = 0; i <= 11; i++) {
      CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255, 0, 0));
    }
  }
  CircuitPlayground.clearPixels();


}
