#include <RobotKit.h>

int leftL, rightL;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pivotLeft(100,200);
  leftL=analogRead(A0);
  pivotRight(100,400);
  rightL=analogRead(A0);  
  stopMotors();
  if(leftL<rightL) pivotLeft(100,400);
  
 //forward(150,100,1000);

}
