//Tomas de-Camino-Beck
// Bubble Sort

#include "Adafruit_CircuitPlayground.h"

byte numbers[9];
int i, j;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  CircuitPlayground.setBrightness(100);
}

void loop() {
  randomize();
  //Algoritmo bubbleSort
  for (i = 0; i <= 9 ; i++) {
    for (j = 0; j <= 9 - i; j++) {
      if (numbers[j] <= numbers[j + 1]) {
        //swap fitnes
        float f = numbers[j];
        numbers[j] = numbers[j + 1];
        numbers[j + 1] = f;
        //prende los leds respectivos para ver el cambio
        CircuitPlayground.setPixelColor(j, CircuitPlayground.strip.Color(numbers[j], 255 - numbers[j], 0));
        CircuitPlayground.setPixelColor(j + 1, CircuitPlayground.strip.Color(numbers[j + 1], 255 - numbers[j + 1], 0));
        delay(200);
      }
    }
  }
  delay(2000);
  CircuitPlayground.clearPixels();
}

void randomize() {
  for (int i = 0; i <= 9 ; i++) {
    numbers[i] = map(random(10), 0, 10, 0, 255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(numbers[i], 255 - numbers[i], 0));
    delay(200);
  }
}


