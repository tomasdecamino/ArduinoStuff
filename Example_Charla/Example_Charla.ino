
#include <Servo.h>  // servo library
Servo servo1; 

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);
}


void loop()
{

  int l = analogRead(A0);
  Serial.println(l);
  servo1.write(map(l,0,1023,0,180));

}

