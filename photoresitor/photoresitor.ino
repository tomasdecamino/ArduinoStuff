#include <Servo.h>
Servo servo1;

void setup() {
  pinMode(A0,INPUT);
  servo1.attach(9);
  Serial.begin(9600);

}

void loop() {
  int valor = analogRead(A0);
  int angulo = map(valor,0,1023,0,180);
  servo1.write(angulo);
  Serial.println(valor);
  delay(100);

}
