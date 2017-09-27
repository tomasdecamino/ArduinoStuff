#include <RobotKit.h>

void setup() {
  // put your setup code here, to run once:
  setMotors();
  pinMode(2,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(100,100);
  int val=digitalRead(2);
  if(val<1){
    pivotLeft(100,500); 
  }
  Serial.println(val);


}
