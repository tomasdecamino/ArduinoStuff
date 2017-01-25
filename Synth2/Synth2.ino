#include <Servo.h> 

Servo myservo;

void setup(){
  myservo.attach(3);
  pinMode(11,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  myservo.write(65);
}

void loop(){
  int val = analogRead(A0);
  int mapval=map(val,800,900,220,880);
  Serial.println(val);
  tone(11,mapval/4);
  tone(9,mapval/2);
  delay(100);
}



