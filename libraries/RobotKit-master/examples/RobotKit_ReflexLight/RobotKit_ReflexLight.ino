#include <RobotKit.h>

void setup() {
  // put your setup code here, to run once:
  setMotors();
  setSensor(A0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = readSensor(A0);
  int pot = map(val,0,1023,0,255); 
  forward(pot, pot, 1023-val);
  pivotLeft(200,random(val));
}
