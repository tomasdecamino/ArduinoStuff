#include <Wire.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_NeoPixel.h>

#define PIN            6
#define NUMPIXELS      16


Adafruit_LSM303 lsm;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



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
  pixels.begin();
}

void loop() 
{
  lsm.read();
  float x=map(lsm.accelData.x,-1000,1000,-3,3);
  float y=map(lsm.accelData.y,-1000,1000,-3,3);
  float z=map(lsm.accelData.y,-1000,1000,-3,3);  
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
  Mouse.move(x,-y,0);
  double point = map(x,-10,10,0,15);
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,150)); // Moderately bright green color.
  }
  pixels.setPixelColor(point, pixels.Color(150,0,0));
  pixels.setPixelColor(point+1, pixels.Color(150,0,0));
  pixels.setPixelColor(point-1, pixels.Color(150,0,0));
  pixels.show();
}

