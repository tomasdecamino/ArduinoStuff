// @author Tomas de Camino Beck
// inventoria.org & funcostarica.org

#include <Servo.h>

Servo miservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);// inicia el pin A0
  miservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);//leer el sensor
  int angle = map(val, 0,1023,0,180);  
  miservo.write(angle);
}
