#include <RobotKit.h>

void setup() {
  // put your setup code here, to run once:
  setMotors();
  setSensor(4);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(4);
  Serial.println(val);
  if (val == 1) {
    forward(100,100);
  } else {
    randomPivot(150,500);
  }
}
