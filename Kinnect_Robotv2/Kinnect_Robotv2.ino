#include <Servo.h>

Servo servoL, servoR;


void setup()
{

  Serial.begin(9600);
  servoL.attach(9);
  servoR.attach(10);
  servoL.write(90);
  servoR.write(90);

}

void loop()
{


  //verifica si hay serial
  char inChar;
  if (Serial.available()) {
    inChar = (char)Serial.read();
    if (inChar == 'f') {
      mForward(0);
    }
    if (inChar == 'b') {
      mBackward(0);
    }
    if (inChar == 'l') {
      mLeft(0);
    }
    if (inChar == 'r') {
      mRight(0);
    }
    if (inChar == 's') {
      mStop();
    }
  }

}


//************* Funciones *****************
//***********************************************

void mBackward(int time) {
  //motor der
  servoL.write(100);
  servoR.write(80);
  delay(time);
}

void mForward(int time) {
  servoL.write(80);
  servoR.write(100);
  delay(time);
  delay(time);
}

void mRight(int time) {
  //motor der
  servoL.write(100);
  servoR.write(100);
  delay(time);
}


void mLeft(int time) {
  servoL.write(80);
  servoR.write(80);
  delay(time);
}

void mStop() {
  servoL.write(90);
  servoR.write(90);
}



