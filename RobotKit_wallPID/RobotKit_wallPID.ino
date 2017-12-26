#include <RobotKit.h>

int dif=0;
int error,errorAnt=0;
const float Kp=1.2;
const float Kd=2.2;

void setup() {
  // put your setup code here, to run once:
  setMotors(); //prepara los motores
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  error = analogRead(A0) - analogRead(A2);
  dif = floor(Kp*(analogRead(A0) - analogRead(A2))+Kd*(errorAnt-error));
  errorAnt=error;
  int d0 = constrain(255 - dif, 0, 255);
  int d1 = constrain(255 + dif, 0, 255);
  if (analogRead(A1) < 950){
    stopMotors();
    delay(200);
    backward(150, 100);
    pivotLeft(200, 450);
  }
  forward(d0, d1,5);
}
