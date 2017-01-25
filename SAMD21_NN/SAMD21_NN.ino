/**
   @author  Tomás de Camino Beck
   @Inventoría Costa Rica
   @ tomas@funcostarica.org
   @version 1.0, 15/11/2015
   Simple perceptron for Bot learning
*/

#include <Servo.h>

//just the mid point for stopping the servos
#define MIDL 90
#define MIDR 90


//**************Class perceptron*************
class perceptron
{

    const float c = 0.00008;//constante de aprendizaje

  public:
    //arrays that hold inputs and weights
    float* inputs;
    float* weights;
    int n; //numero de entradas

    perceptron(int ninputs) {
      n = ninputs;
      inputs = new float[n];
      weights = new float[n];
      inputs[n - 1] = 1;//bias
      for (int i = 0; i < n; i++) {
        // The weights are picked randomly to start.
        //a trick to get values from -1 to 1
        weights[i] = (float)random(-1000, 1000) / 1000;
      }
    }

    //reset weights to random values
    void randomize() {
      for (int i = 0; i < n; i++) {
        // The weights are picked randomly to start.
        weights[i] = (float)random(-1000, 1000) / 1000;
      }
    }

    //training function
    void train(int desired, float guess) {
      float error = desired - guess;
      for (int i = 0; i < n; i++) {
        weights[i] += c * error * inputs[i];
      }
    }

    //forward function
    float feedForward() {
      float sum = 0;
      for (int i = 0; i < n; i++) {
        sum += inputs[i] * weights[i];
      }

      return activate(sum);
    }


  private:
    //activation function
    int activate(float sum) {
      //regresa 1 si es positivo, -1 si negativo.
      if (sum > 0) {
        return 1;
      }
      else {
        return -1;
      }
    }



};

//*************main code***************

perceptron brainL(3);
perceptron brainR(3);

Servo servoL, servoR;


void setup()
{
  servoL.attach(8);
  servoR.attach(6);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  randomSeed(analogRead(A0));
  brainL.randomize();
  brainR.randomize();
  SerialUSB.begin(9600);
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

  //use this to move servos left and right
  moveLeft(resL);
  moveRight(resR);
  delay(200);//let move for some time then stop
  stopServo();
  delay(100);
  SerialUSB.println(r );
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


//******servo movement functions ***************
void moveLeft(int d) {
  if (d > 0) {
    servoL.write(180);
  } else {
    servoL.write(0);
  }
}

void moveRight(int d) {
  if (d > 0) {
    servoR.write(180);
  } else {
    servoR.write(0);
  }
}


void stopServo() {
  servoR.write(MIDR);
  servoL.write(MIDL);

}




