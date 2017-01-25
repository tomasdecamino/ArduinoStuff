#include <Servo.h> 
 
Servo myservo;  // pepara el objeto servo 
                 

void setup() 
{ 
  myservo.attach(6); //conecta con el pin 6
} 
 
 
void loop() 
{ 
 
    myservo.write(90);  //Mueve el servo a un angulo de 90
    
}
