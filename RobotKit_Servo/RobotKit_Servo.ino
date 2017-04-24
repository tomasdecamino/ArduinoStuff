#include <Servo.h>
#include <RobotKit.h>


int leftL, rightL;
Servo garra;

void setup() {
  // put your setup code here, to run once:
  setMotors();
  pinMode(A0, INPUT);
  Serial.begin(9600);
  garra.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  pivotLeft(100, 200);
  pivotRight(100, 400);
  stopMotors();
  forward(150, 100, 1000);
  garra.write(100);
  delay(300);
  garra.write(160);

}
