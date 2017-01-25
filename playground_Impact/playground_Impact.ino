/*Tomas de Camino Beck
  www.funcostarica.org
  Simple medidor de impacto
*/
#include <Adafruit_CircuitPlayground.h>

//Rango de temperaturas que marcan los LEDs
#define MIN 0
#define MAX -10

int maxImpact = MIN;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}


void loop() {
  float impact = CircuitPlayground.motionZ();
  if (impact < maxImpact) {
    maxImpact = impact;
  }
  pixelMeter(maxImpact, MIN, MAX);
  if (CircuitPlayground.leftButton()) {
    CircuitPlayground.clearPixels();
    maxImpact = MIN;
    delay(500);
  }
  Serial.println(maxImpact);
}

void pixelMeter(float value, float minimum, float maximum) {
  int p = map(value, minimum, maximum, 0, 9);
  CircuitPlayground.clearPixels();
  for (int i = 0; i <= p; i++) {
    int c = map(i, 0, 9, 0, 255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(c, 255 - c, 0));
  }
}

