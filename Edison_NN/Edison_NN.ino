/**
 * @author  Tomás de Camino Beck
 * @Inventoría Costa Rica
 * @ tomas@funcostarica.org
 * @version 1.0, 15/11/2015
 * Simple perceptron for Bot learning
 */

#include <SoftwareServo.h>

//just the mid point for stopping the servos
#define MIDL 79
#define MIDR 77


//**************Class perceptron*************
class perceptron
{

    const float c = 0.00008;


  public:
    //arrays that hold inputs and weights
    float* inputs;
    float* weights;
    int n;

    perceptron(int ninputs) {
      n = ninputs;
      inputs = new float[n];
      weights = new float[n];
      inputs[n - 1] = 1;
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
    void train(int desired, float f) {
      int guess = f;
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

SoftwareServo servoL, servoR;



void setup()
{
  servoL.attach(8);
  servoR.attach(6);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  randomSeed(analogRead(A0));
  brainL.randomize();
  brainR.randomize();
  //Serial.begin(9600);
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
  delay(30);//let move for some time then stop
  stopServo();
  delay(5);
  //train
  brainL.train(eval(l,r), resL);
  brainR.train(eval(r,l), resR);


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

//the desired output is sensor with similar value
int maximize(int s1, int s2){
  if(abs(s1-s2)<200) return 1;
  else return -1;
}


//******servo movement functions ***************
void moveLeft(char d) {
  if (d > 0) {
    servoL.write(0);
  } else {
    servoL.write(180);
  }
}

void moveRight(char d) {
  if (d > 0) {
    servoR.write(180);
  } else {
    servoR.write(0);
  }
}

void moveLeft2(char d) {
  if (d > 0) {
    servoL.write(180);
  } else {
    servoL.write(MIDL);
  }
}

void moveRight2(char d) {
  if (d > 0) {
    servoR.write(0);
  } else {
    servoR.write(MIDR);
  }
}



void moveServo(char d) {
  if (d > 0) {
    servoR.write(180);
    servoL.write(0);
  } else {
    servoR.write(0);
    servoL.write(180);
  }
}

void stopServo() {
  servoR.write(MIDR);
  servoL.write(MIDL);

}

void turnServo(char d) {
  if (d > 0) {
    servoR.write(0);
    servoL.write(0);
  } else {
    servoR.write(180);
    servoL.write(180);
  }
}


