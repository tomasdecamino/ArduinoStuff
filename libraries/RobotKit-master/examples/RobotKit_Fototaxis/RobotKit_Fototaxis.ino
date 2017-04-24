//Tomas de Camino Beck
//www.funcostarica.org

#include <RobotKit.h>
int luzAntes, luzAhora;//guarda información de luz

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  setSensor(A0); //prepara el sensor conectado a aA0
  luzAhora = readSensor(A0);//para inicializar
  randomSeed(A0);//punto de inicio del generador de aleatorios
}

void loop() {
  luzAhora = readSensor(A0);
  if (luzAhora >= luzAntes) {
    int t = random(600);
    pivotLeft(100, t);
  }
  forward(150, 50);
  luzAntes = luzAhora;
}
