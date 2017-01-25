//cargar libreria
#include <RobotKit.h>



void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  setSensor(A0); //prepara el sensor conectado a aA0
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  pointLight(A0); //apunta el robot hacia la luz
  forward(100, 200); //camina hacia adelante por 200 milisegundos
}
