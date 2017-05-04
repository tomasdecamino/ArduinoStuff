/**
   @author  Tomás de Camino Beck
   @Inventoría Costa Rica
   @ tomas@funcostarica.org
   @version 1.0, 30/04/2017
   Simple perceptron for Bot learning
*/

#include <RobotKit.h>
#include <Perceptron.h>


//*************main code***************

perceptron brain(3);


void setup()
{
  setMotors();
  setSensor(A0);
  setSensor(A1);
  randomSeed(readSensor(A0));
  //inicia los perceptrones con valores aleatorios
  brain.randomize();


  //constante de arendizaje 0.000008
  brain.setTraining(0.000001);
  //tiempo antes de empezar
  delay(2000);

}

void loop()
{

  //read light seonsors
  int l = analogRead(A0);
  int r = analogRead(A1);


  //set inputs
  brain.inputs[0] = l;
  brain.inputs[1] = r;

  //dispara la neurona para ver cual es
  //la predicción
  int res = brain.feedForward();

  //si res < 0 entonces teinde a doblar hacia la derecha
  //de lo contrario a la izquierda
  if (res < 0) {
    forward(130, 70, 20);
  }else{
    forward(70, 130, 20);
  }
  //revisa si efectivamente el
  //movimiento tiende a mejorar
  //la dirección a la luz
  int obs = eval(l, r);
  
  //entrena la neurona comparando lo obtenido "res"
  //con el deseado "obs"
  brain.train(obs, res);
  
  //algo de aleatoriedad
  //para evitar que se quede solo con una
  //posibilidad cuando hay mejores
  randomPivot(100,30);
}

//***** función de evaluación******

int eval(int s1, int s2) {
  if (s1 > s2) {
    return 1;
  }
  else {
    return -1;
  }
}





