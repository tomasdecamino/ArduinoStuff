#include <RobotKit.h>
void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(100, 500);
  stopMotors();
  delay(1000);

}
