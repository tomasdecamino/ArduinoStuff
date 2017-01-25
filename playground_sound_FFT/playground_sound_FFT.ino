#include <Adafruit_CircuitPlayground.h>
#include <Perceptron.h>

perceptron soundPerceptron(129);//fourth is for bias

void setup()
{
  CircuitPlayground.begin();
  randomSeed(CircuitPlayground.readCap(3));
  soundPerceptron.randomize();//weight initialization
  soundPerceptron.inputs[128]=-1 
  Serial.begin(115200);
};
void loop()
{
  for (int i = 0; i < 128; i++) {
    int val = analogRead(A4);
    soundPerceptron.inputs[i]  = val / 4 - 128;
//    Serial.println();
  };
  Serial.println("start");


};
