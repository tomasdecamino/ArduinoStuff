#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  //digitalWrite(2,HIGH);
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  Mouse.begin();
  Keyboard.begin();
}

void loop() 
{
  lsm.read();
  Serial.print("Accel X: "); 
  Serial.print((int)lsm.accelData.x); 
  Serial.print(" ");
  Serial.print("Y: "); 
  Serial.print((int)lsm.accelData.y);       
  Serial.print(" ");
  Serial.print("Z: "); 
  Serial.println((int)lsm.accelData.z);
  Serial.print(digitalRead(A0));
  //delay(10);
  if(digitalRead(A0)==0){
    Keyboard.write('a');
    delay(1000); 
  }
  if(digitalRead(A1)==0){
    Keyboard.write('s');
    delay(1000); 
  }  
  if(digitalRead(A2)==0){
    Keyboard.write('d');
    delay(1000); 
  }
  if(lsm.accelData.x>400){
    Mouse.move(5,0,0); 
  }
  if(lsm.accelData.x<-400){
    Mouse.move(-5,0,0); 
  }
  if(lsm.accelData.y>500){
    Mouse.move(0,-5,0); 
  }
  if(lsm.accelData.y<-400){
    Mouse.move(0,5,0); 
  }
}

