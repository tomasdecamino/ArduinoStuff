//Tomas de Camino Beck
//www.funcostarica.org

// learns to recognize a set of notes
// choose notes you want ro recognize, and then have CP to turn
//green. Then choose notes you don't wnat and train to turn red...

#include <Adafruit_CircuitPlayground.h>
#include "Perceptron.h"

#define BINS   32          // The number of FFT frequency bins

perceptron notePerceptron(33);// setup perceptron with 33 entries

float initW[33]={-4.85,-8.15,-2.89,-8.66,-5.61,4.22,-4.66,-1.11,1.43,6.79,0.98,4.48,0.10,6.63,2.13,4.95,9.76,1.60,3.67,-0.61,2.38,-1.73,-2.55,-2.96,-0.32,-2.83,3.74,2.64,2.23,-0.13,-1.30,4.64};

void setup() {
  CircuitPlayground.begin();  // Set up the board library and serial
  Serial.begin(9600);
  randomSeed(CircuitPlayground.readCap(3));
  notePerceptron.randomize(); //randomize perceptron
  notePerceptron.setTraining(0.08);//set learning speed
  notePerceptron.weights=initW;
  pinMode(2,OUTPUT);
};
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
    digitalWrite(2,HIGH);
  }
  else {
    c = CircuitPlayground.strip.Color(255, 0, 0);
    digitalWrite(2,LOW);

  }

  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, c);
  }

  delay(1000);

  //is switch then in training mode
  if (CircuitPlayground.slideSwitch()) {
    //press button when playground makes classifies incorrectly
    if (CircuitPlayground.rightButton()) {
      CircuitPlayground.clearPixels();
      //desired, guess
      notePerceptron.train(-guess, guess);
      //led blue to indicate it was trained
      CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(0, 0, 255));
    }
    if (CircuitPlayground.leftButton()) {
      CircuitPlayground.clearPixels();
      //desired, guess
      notePerceptron.train(-guess, guess);
      //led blue to indicate it was trained
      CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(255, 0, 0));
    }

    for (i = 0; i < 32; i++) {
      Serial.print(notePerceptron.weights[i]);
      Serial.print(",");
    }
    Serial.println("");
  }

}
