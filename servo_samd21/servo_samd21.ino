
#include <Servo.h>

Servo myservo;
Servo myservo2;

void setup() {
  myservo.attach(9);
  myservo2.attach(6);
}

void loop() {
  myservo.write(90);
  myservo2.write(90);
  delay(1000);
  myservo.write(70);
  myservo2.write(110);
  delay(500);
  myservo.write(90);
  myservo2.write(90);
  delay(1000);  
  myservo.write(110);
  myservo2.write(70);
  delay(100);
}

