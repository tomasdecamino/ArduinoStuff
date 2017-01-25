
#include <Servo.h>


int m = 0; 

Servo control;

void setup() {

  control.attach(9);  
  Serial.begin(9600);  

}

void loop() {

  control.writeMicroseconds(m);

  if (Serial.available())
    m = Serial.parseInt();   

}
