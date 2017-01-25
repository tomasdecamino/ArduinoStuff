#include <Servo.h>

Servo miservo;

void setup(){
  miservo.attach(9);//conectar servo a pin 9
}

void loop(){
  miservo.write(0);// mueve servo a 0 grados
  delay(500);
  miservo.write(90);//mueve servo a 180
  delay(500);
}
