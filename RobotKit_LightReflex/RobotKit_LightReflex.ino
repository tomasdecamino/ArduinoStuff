//cargar libreria
#include <RobotKit.h>

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  setSensor(A0); //prepara el sensor conectado a aA0
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = map(readSensor(A0), 0, 1023, 1000, 0); //apunta el robot hacia la luz
  randomPivot(100, val);
  forward(100, val); //camina hacia adelante por 200 milisegundos
}
