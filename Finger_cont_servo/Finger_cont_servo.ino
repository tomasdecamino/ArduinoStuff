
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 


void loop() 
{ 
  int val = analogRead(A1);
  if(val>700){
    moveLeft(1);
  } 
  if(val<300){
    moveRight(1);
  }
}

void moveRight(int s){
  for(int i=0;i<s;i++){
    myservo.write(130);
    delay(20);
    myservo.write(90);
    delay(20);
  } 
}

void moveLeft(int s){
  for(int i=0;i<s;i++){
    myservo.write(65);
    delay(20);
    myservo.write(90);
    delay(20);
  } 
}




