//@author> Tomas de Camino

#include <Servo.h> 
int incomingByte = 0;
int ang = 90; //store the angle

Servo myservo;  

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(ang);
} 


void loop() 
{ 
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:

    incomingByte = Serial.read();
    if(incomingByte=='L'){
      ang+=2;
    }
    else if(incomingByte=='R'){
      ang-=2;
    }else{
      ang =90;
    }
  }
  myservo.write(constrain(ang,0,180));
  
} 

