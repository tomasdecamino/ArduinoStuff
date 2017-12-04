/*Tomas de Camino Beck
  www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#define CLAPTEMPO 100
#define TH 900

int count = 0;
double tiempo = 0;

void setup() {
  //inicializa el Playground
  CircuitPlayground.begin();
  Serial.begin(9600);
}

void loop() {
  if (CircuitPlayground.soundSensor() > TH) {
    count++;
    CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(0, 255, 0));
    delay(CLAPTEMPO);
    tiempo = millis();
    while ((millis() - tiempo) < 500) {
      if (CircuitPlayground.soundSensor() > TH) {
        count++;
        delay(CLAPTEMPO);
      }
    }
    for (int i = 0; i < count;i++) {
      CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255, 0, 0));
    }
    
    ////algo pasa
    count=0;
    delay(1000);
  } else {
    CircuitPlayground.clearPixels();
  }

}


