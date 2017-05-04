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

int currentLight = 0, lightBefore = 0;

void setup()
{
  setMotors();
  setSensor(A0);
  setSensor(A1);
  pinMode(13,OUTPUT);
  randomSeed(readSensor(A0));
  //inicia los perceptrones con valores aleatorios
  brain.randomize();

  startLED(3);


  //constante de arendizaje 0.000008
  brain.setTraining(0.002);
  //tiempo antes de empezar
  delay(2000);
}

void loop()
{

  //read light seonsors
  lightBefore = currentLight;
  currentLight = analogRead(A0);

  //set inputs
  brain.inputs[0] = lightBefore;
  brain.inputs[1] = currentLight;

  
  //dispara la neurona para ver cual es
  //la predicción
  int res = brain.feedForward();

  //si res > 0 entonces se mueve hacia adelante
  //de lo contrario gira a la izquierda
  if (res > 0) {
    forward(150, 100);
  } else {
    pivotLeft(200,50);
  }
  //revisa si efectivamente el
  //movimiento tiende a mejorar
  //la intensidad de la luz
  int obs = eval(lightBefore, currentLight);

  //entrena la neurona comparando lo obtenido "res"
  //con el deseado "obs"
  if(obs==res)setLED(0,255,0);
  else setLED(255,0,0);;
  brain.train(obs,res);

}

//***** función de evaluación******

int eval(int val1, int val2) {
  if (val1 >= val2) {
    return 1;
  }
  else {
    return -1;
  }
}





