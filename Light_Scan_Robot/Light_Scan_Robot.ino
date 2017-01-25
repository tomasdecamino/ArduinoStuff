#include <Servo.h>

#define LEFTDIR 10
#define RIGHTDIR 11
#define LEFTSPEED 5
#define RIGHTSPEED 6

#define MIN 0
#define MAX 1023

int leftL = 0;
int rightL = 0;

Servo servo1;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(2);
  servo1.write(90);
  pinMode(LEFTDIR, OUTPUT);
  pinMode(LEFTSPEED, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);
  pinMode(RIGHTSPEED, OUTPUT);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  Serial.begin(9600);
}

void loop() {

  // put your main code here, to run repeatedly:
  int leftS = lightToSpeed(leftL)+10;
  int rightS = lightToSpeed(rightL);
  Serial.print(leftL);
  Serial.print(',');
  Serial.println(leftS);
  analogWrite(LEFTSPEED, leftS);
  analogWrite(RIGHTSPEED, rightS);
  rightL = leftL = 0;
  servo1.write(0);
  delay(500);
  rightL = analogRead(A0);
  servo1.write(180);
  delay(500);
  leftL = analogRead(A0);
}

int lightToSpeed(int l) {
  int  state = map(l, MIN, MAX, 0, 5);
  switch (state) {
    case 1:
      return 100;
      break;
    case 2:
      return 100;
      break;
    case 3:
      return 105;
      break; 
    case 4:
      return 110;
      break;
    case 5:
      return 150;
      break;                       
    default:
      return 85;
      break;
  }
}

