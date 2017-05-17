#include <RobotKit.h>
void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
    startLED(3);
    setLED(255,100,100);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(80, 500);
  //stopMotors();
  //delay(1000);

}
