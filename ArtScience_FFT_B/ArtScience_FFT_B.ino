// Fast Forier Transform Test Program for Circuit Playground
// Mike Barela for Adafruit Industries    September, 2016

#include <Adafruit_CircuitPlayground.h>
#include "Perceptron.h"

#define BINS   32          // The number of FFT frequency bins

perceptron noisePerceptron(33);

void setup() {
  CircuitPlayground.begin();  // Set up the board library and serial
  Serial.begin(9600);
  randomSeed(CircuitPlayground.readCap(3));
  noisePerceptron.randomize();
  noisePerceptron.setTraining(0.08);

}

void loop() {
  uint8_t i, j;
  uint16_t spectrum[BINS];


  //toma el promedio de 5 muestras
  CircuitPlayground.mic.fft(spectrum);

  for (i = 0; i < 32; i++) {
    noisePerceptron.inputs[i] = spectrum[i];
  }



  float guess = noisePerceptron.feedForward();

  uint32_t c;
  if (guess == 1) {
    c = CircuitPlayground.strip.Color(0, 255, 0);
    Serial.println("Match");
  }
  else {
    c = CircuitPlayground.strip.Color(255, 0, 0);
    Serial.println("No Match");

  }

  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, c);
  }
  
  delay(1000);
  if (CircuitPlayground.slideSwitch()) {
    Serial.println("Train Mode");
    if (CircuitPlayground.rightButton()) {
      Serial.println("reinforced");
      CircuitPlayground.clearPixels();
      //desired, guess
      noisePerceptron.train(-guess, guess);
      CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(0, 0, 255));
      delay(1000);
    }
  }

}
