#include <Servo.h>

Servo servo1, servo2;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(7);
  servo2.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo2.write(0);
  servo1.write(80);
  delay(1500);
}
