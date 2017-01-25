#include <Servo.h>

Servo servoL, servoR;

void setup() {
  pinMode(A0,INPUT);
  servoR.attach(5);
}

void loop() {
  int val = analogRead(A0);
  int m = map(val,0,1023,0,50);
  servoR.writeMicroseconds(1320+m);
  delay(50);
}
