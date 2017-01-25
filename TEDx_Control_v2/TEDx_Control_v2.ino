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
  float x=map(lsm.accelData.x,-1000,1000,-10,10);
  float y=map(lsm.accelData.y,-1000,1000,-10,10);
  float z=map(lsm.accelData.y,-1000,1000,-10,10);  
  Serial.print("Accel X: "); 
  Serial.print(x); 
  Serial.print(" ");
  Serial.print("Y: "); 
  Serial.print(y);       
  Serial.print(" ");
  Serial.print("Z: "); 
  Serial.println(z);
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
  Mouse.move(x,-y-2,0);
}

