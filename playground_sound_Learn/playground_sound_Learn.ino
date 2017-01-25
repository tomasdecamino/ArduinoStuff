#include <Adafruit_CircuitPlayground.h>
#include <Perceptron.h>

perceptron soundPerceptron(129);//fourth is for bias

void setup()
{
  CircuitPlayground.begin();
  randomSeed(CircuitPlayground.readCap(3));
  soundPerceptron.randomize();//weight initialization
  soundPerceptron.inputs[128] = -1;
  Serial.begin(115200);
};
void loop()
{
  for (int i = 0; i < 128; i++) {
    int val = analogRead(A4);
    soundPerceptron.inputs[i]  = val;// / 4 - 128;
    //    Serial.println();
  };
  //make a guess
  float guess = soundPerceptron.feedForward();
  //press button if guess incorrect
  if (CircuitPlayground.rightButton()) {
    CircuitPlayground.clearPixels();
    soundPerceptron.train(-guess, guess);
    delay(1000);
  }


  //change color
  uint32_t c;
  if (guess == 1) {
    c = CircuitPlayground.strip.Color(0, 255, 0);
    Serial.println("Match");
  }
  else {
    c = CircuitPlayground.strip.Color(255, 0, 0);
    Serial.println("No Match");

  }

  //update pixels
  for (int i = 3; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, c);
  }

};
