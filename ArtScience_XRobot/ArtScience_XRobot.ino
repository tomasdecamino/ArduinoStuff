#include <Servo.h>
#include <Adafruit_CircuitPlayground.h>

Servo servoL, servoR;
int origin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  CircuitPlayground.begin();
  servoL.attach(9);
  servoR.attach(2);
}

void loop() {
  // prende las luces
  if (CircuitPlayground.slideSwitch()) {
    CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(255, 0, 100));
    CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(255, 0, 100));
    forward(10);
    Serial.println(CircuitPlayground.motionZ());
  } else {
    CircuitPlayground.setPixelColor(0, CircuitPlayground.strip.Color(0, 0, 255));
    CircuitPlayground.setPixelColor(9, CircuitPlayground.strip.Color(0, 0, 255));
    delay(1500);
  }
  //apaga las luces
  CircuitPlayground.clearPixels();
  stopBot(500);
}

void forward(int t) {
  servoR.write(130);
  servoL.write(50);
  delay(t);
}

void forward() {
  servoR.write(130);
  servoL.write(50);
}

void stopBot() {
  servoR.write(90);
  servoL.write(90);
}

void stopBot(int t) {
  servoR.write(90);
  servoL.write(90);
  delay(t);
}

void backward() {
  servoL.write(130);
  servoR.write(50);
}

void pivotLeft() {
  servoR.write(130);
  servoL.write(130);
}

void pivotLeft(int t) {
  servoR.write(130);
  servoL.write(130);
  delay(t);
}

void pivotRight() {
  servoR.write(50);
  servoL.write(50);
}

void pivotRight(int t) {
  servoR.write(50);
  servoL.write(50);
  delay(t);
}

