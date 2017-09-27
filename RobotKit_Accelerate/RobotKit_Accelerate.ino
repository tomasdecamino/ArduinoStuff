#include <RobotKit.h>

int delta =10;
int speed=0;

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(speed, 500);
  speed+=delta;

}
