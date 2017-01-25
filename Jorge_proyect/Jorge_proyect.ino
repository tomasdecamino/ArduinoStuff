#include <Servo.h>
Servo myServo;
int angle = 90;
int maxLux =0;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  // myServo.write(90);
}

void loop(){
 int lux = analogRead(A0);
 Serial.println(lux);
 findMax();
 //Serial.println(angle);
 delay(10000);
 
}

void toOrigin(){
  for(int i = angle; i=90;i+=1){
    myServo.write(i);
    delay(500); 
  }
  
}

void moveUp(){
 if(angle>65){
   angle-=1;
   myServo.write(angle);
   delay(500);
 } 
}


void moveDown(){
 if(angle<=90){
   angle+=1;
   myServo.write(angle);
   delay(500);
 } 
}

void findMax(){
 int lux = analogRead(A0);
 maxLux = lux;
 while((lux>=maxLux)&&(angle>65)){
  moveUp();
  Serial.println(angle);
  Serial.println(lux);
  Serial.print(maxLux);
  lux = analogRead(A0);
 }
 maxLux =analogRead(A0);
 if(angle =65){
   while((lux>=maxLux)&&(angle<90)){
    moveDown();
    Serial.println(angle);
    Serial.println(lux);
    lux = analogRead(A0);
   }   
 }
  
}
