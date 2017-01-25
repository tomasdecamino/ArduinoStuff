#include <RobotKit.h>
void setup(){
  setMotors();
}
void loop(){
  //acá escribimos los comandos de movimiento
  forward(100,200); // mueve hacia adelante por 200 milisegundos
  delay(500); //espera medio segundo 
  pivotRight(100,200);
  delay(500); //espera medio segundo 
  
  //rd(100,200);
}
