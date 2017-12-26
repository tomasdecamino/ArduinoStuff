#include <RobotKit.h>
void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(9));
  if (!digitalRead(12)) {
    pivotLeft(255, 200);//da vuelta 90 grados
  }
  if (!digitalRead(2)) {
    pivotRight(255, 200);//da vuelta 90 grados
  }
  forward(255, 5);
}
