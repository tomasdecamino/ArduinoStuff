#include <Ultrasonic.h>
#include <Servo.h>


#define TRIGGER_PIN  12
#define ECHO_PIN     13


#define LEFTDIR 10
#define RIGHTDIR 11
#define LEFTSPEED 5
#define RIGHTSPEED 6

#define MIN 0
#define MAX 1023

int leftL = 0;
int rightL = 0;
float cm, cmR, cmL;
int leftS, rightS;

boolean dir = true;
boolean sDir = true;

Servo servo1;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
  // put your setup code here, to run once:
  servo1.attach(2);
  servo1.write(90);
  pinMode(LEFTDIR, OUTPUT);
  pinMode(LEFTSPEED, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);
  pinMode(RIGHTSPEED, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  Serial.begin(9600);

}

void loop() {
  servo1.write(160);
  delay(300);
  cmL = distance(3);
  servo1.write(30);
  delay(500);
  cmR = distance(3);
  if (cmL == cmR) {
    analogWrite(LEFTSPEED, 150);
    analogWrite(RIGHTSPEED, 150 + 60);
  } else {
    if (cmL < cmR) {
      analogWrite(LEFTSPEED, 150);
      analogWrite(RIGHTSPEED, 0);
    } else {
      analogWrite(LEFTSPEED, 0);
      analogWrite(RIGHTSPEED, 150 + 60);
    }
  }
  delay(300);
  analogWrite(LEFTSPEED, 0);
  analogWrite(RIGHTSPEED, 0);
  Serial.print(cmL);
  Serial.print(" , ");
  Serial.println(cmR);

}

float distance(int t) {
  float cm=0;
  long microsec = ultrasonic.timing();
  for (int i = 0; i < t; i++) {
    microsec = ultrasonic.timing();
    cm += ultrasonic.convert(microsec, Ultrasonic::CM);
  }
  return cm/t;
}



