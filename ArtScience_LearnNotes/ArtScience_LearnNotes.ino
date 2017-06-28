//Tomas de Camino Beck
//www.funcostarica.org

// learns to recognize a set of notes
// choose notes you want ro recognize, and then have CP to turn
//green. Then choose notes you don't wnat and train to turn red...

#include <Adafruit_CircuitPlayground.h>
#include "Perceptron.h"

#define BINS   32          // The number of FFT frequency bins

perceptron notePerceptron(33);// setup perceptron with 33 entries

void setup() {
  CircuitPlayground.begin();  // Set up the board library and serial
  Serial.begin(9600);
  randomSeed(CircuitPlayground.readCap(3));
  notePerceptron.randomize(); //randomize perceptron
  notePerceptron.setTraining(0.08);//set learning speed
}

void loop() {
  uint8_t i, j;
  uint16_t spectrum[BINS];


  //take a sample of the mic and get spectrum
  CircuitPlayground.mic.fft(spectrum);

  //set perceptron inputs
  for (i = 0; i < 32; i++) {
    notePerceptron.inputs[i] = spectrum[i];
  }


  // perceptron makes a guess
  float guess = notePerceptron.feedForward();

  //set green or red
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
  
  //is switch then in training mode
  if (CircuitPlayground.slideSwitch()) {
    Serial.println("Train Mode");
    //press button when playground makes classifies incorrectly
    if (CircuitPlayground.rightButton()) {
      Serial.println("reinforced");
      CircuitPlayground.clearPixels();
      //desired, guess
      notePerceptron.train(-guess, guess);
      //led blue to indicate it was trained
      CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(0, 0, 255));
      delay(1000);
    }
  }

}
