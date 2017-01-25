#include <Servo.h>

Servo servo1;

const int sensorPin = 0;
const int sensorPin2 = 1;
const int ledPin = 9;


int lightLevel, rotation =90;
int lightLevel2;
int minlevel = 1023;
int maxlevel=0;

  
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  servo1.attach(10);
 calibrate();
}


void loop(){


  lightLevel = analogRead(sensorPin);
  lightLevel2 = analogRead(sensorPin2);
  //delay(500);
  Serial.println(abs(lightLevel-lightLevel2));
  if(abs(lightLevel-lightLevel2)>maxlevel){
      seekLight();  // busca la luz
  }else{
   rotation = 90; 
  }
  servo1.write(rotation);
  
}


void seekLight()
{
  //los valores del sensor hay que calibrarlos con map
  //aunque esto no es necesario hace que los movimientos
  //sean mas estables
  int L = map(lightLevel, 0, 1023, 0, 255);
  int R = map(lightLevel2, 0, 1023, 0, 255);
  //Serial.print(L);
  //Serial.print(",");
  //Serial.println(R);
  if(L>R+minlevel){
    rotation += 1;
  } else if(R>L+minlevel){
    rotation -= 1;
  }
  rotation = constrain(rotation,0,180);
} 

void calibrate(){
  for(int i=0; i<=180; i++){
   lightLevel = analogRead(sensorPin);
   lightLevel2 = analogRead(sensorPin2);
   //Serial.print(lightLevel);
   //Serial.print(",");
   //Serial.println(lightLevel2);
   int dif =abs(lightLevel-lightLevel2);
   //Serial.println(dif);
   if(minlevel>dif){
     minlevel = dif;
   }
   if(maxlevel<dif){
     maxlevel = dif;
   }
  delay(100);
   servo1.write(i);
 //Serial.print(minlevel);
 //Serial.print(",");
 //Serial.println(maxlevel);
 } 
 Serial.print(minlevel);
 Serial.print(",");
 Serial.println(maxlevel);
}


