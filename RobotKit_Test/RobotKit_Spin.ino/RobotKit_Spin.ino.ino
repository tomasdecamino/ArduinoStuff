//incuir libreria
#include <RobotKit.h>

void setup() {
  // put your setup code here, to run once:
  setMotors();//prepara los motores
}

void loop() {
  // put your main code here, to run repeatedly:
  pivotLeft(100,10000); //adelante potencia 100, por 500 milisegundos
  stopMotors();//detiene los motores
  delay(500); //espera 500 milisegundos                                                                       
}
