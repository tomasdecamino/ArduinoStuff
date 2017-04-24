//cargar libreria
#include "Perceptron.h"
#include <RobotKit.h>
//#include <IRremote.h>

int RECV_PIN = 7;
float guess = 0;
boolean training = true;

IRrecv irrecv(RECV_PIN);
decode_results results;
perceptron lightPerceptron(3);

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  setSensor(A0); //prepara el sensor conectado a aA0
  irrecv.enableIRIn();
  Serial.begin(9600);
  lightPerceptron.randomize();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (results.value == 0) {
    Serial.println("look");
    pivotLeft(80, 230);
    stopMotors();
    lightPerceptron.inputs[0] = readSensor(A0);
    pivotRight(80, 400);
    stopMotors();
    lightPerceptron.inputs[1] = readSensor(A0);
    guess = lightPerceptron.feedForward();
    pivotLeft(80, 230);
    stopMotors();
    (guess > 0) ? pivotLeft(80, 200) : pivotRight(80, 230);
    stopMotors();
  }
  //espera al entrenador
  results.value = 1;
  if (training) {
    irrecv.decode(&results);
    Serial.println(results.value);
    if (results.value == 16761405) {
      training=false;
      results.value = 0;
    }
    if (results.value == 16769055) {
      lightPerceptron.train(-guess, guess);
      Serial.println("train");
      results.value = 0;
    }
    if (results.value == 16754775) {
      Serial.println("move");
      //forward(100, 500);
      stopMotors();
      results.value = 0;
    }
    Serial.println("end");
    irrecv.resume();
    delay(1000); //espera un segundo
  } else {
   // forward(100, 200);
    results.value = 0;
  }
}
