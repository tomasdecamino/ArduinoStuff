#include <Servo.h>

Servo miservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  miservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  int ang = map(val,0,1023,0,180);
  miservo.write(ang);

}
