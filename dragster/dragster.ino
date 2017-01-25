#include <Servo.h>

Servo drive, steer;

void setup() {
  // put your setup code here, to run once:
  drive.attach(2);
  steer.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  drive.write(0);
  steer.write(180);
  delay(500);
  steer.write(90);
  delay(500);
  steer.write(0);
  delay(500);

}
