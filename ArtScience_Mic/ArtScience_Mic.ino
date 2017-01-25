/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

#define MID 340 //calibra el punto medio

long loud = 0;//suma las amplitudes

void setup() {
  //inicializa el Playground
  CircuitPlayground.begin();
  Serial.begin(9600);
}

void loop() {
  // codigo que queda en loop cada 4 microsegundos
  for (int i = 0; i < 10; i++) {
    //primero calcula la amplitud
    int dif = CircuitPlayground.soundSensor() - MID;
    //luego hace la sumatoria
    loud += abs(dif);
  }
  Serial.println(loud);
  //muestra el volumen en pixeles
  pixelMeter(loud, 10, 3000);
  loud = 0;
}

void pixelMeter(float value, float minimum, float maximum) {
  int p = map(value, minimum, maximum, 0, 9);
  CircuitPlayground.clearPixels();
  for (int i = 0; i <= p; i++) {
    int c = map(i, 0, 9, 0, 255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(c, 255 - c, 0));
  }
}
