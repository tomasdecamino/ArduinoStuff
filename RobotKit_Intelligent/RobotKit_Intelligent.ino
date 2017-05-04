/**
   @author  Tomás de Camino Beck
   @Inventoría Costa Rica
   @ tomas@funcostarica.org
   @version 1.0, 15/11/2015
   Simple perceptron for Bot learning
*/

#include <RobotKit.h>
#include <Perceptron.h>


//*************main code***************

perceptron brainL(3);
perceptron brainR(3);


void setup()
{
  setMotors();
  setSensor(A0);
  setSensor(A1);
  randomSeed(readSensor(A0));
  //inicia los perceptrones con valores aleatorios
  brainL.randomize();
  brainR.randomize();

  //constante de arendizaje 0.00008
  brainL.setTraining(0.000008);
  brainR.setTraining(0.000008);

  Serial.begin(9600);
  //delay(5000);

}

void loop()
{

  //read light seonsors
  int l = analogRead(A0);
  int r = analogRead(A1);


  //set inputs
  brainL.inputs[0] = l;
  brainL.inputs[1] = r;
  brainR.inputs[0] = l;
  brainR.inputs[1] = r;

  //feed forward and calculate weighted sum
  int resL = brainL.feedForward();
  int resR = brainR.feedForward();

  //si resR > 0 entonces teinde a doblar hacia la derecha
  //y si resL > 0 entonces a la izquierda
  if (resR > 0) forward(120, 80, 20);
  if (resL > 0) forward(80, 120, 20);
  //delay(200);//let move for some time then stop
  //train
  brainL.train(eval(l, r), resL);
  brainR.train(eval(r, l), resR);


}

//***** sensor functions******

int eval(int s1, int s2) {
  if (s1 > s2) {
    return 1;
  }
  else {
    return -1;
  }
}





