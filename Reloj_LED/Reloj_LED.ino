//Arduino 1.0+ Only
//Arduino 1.0+ Only

#include "Wire.h"
#include <Adafruit_NeoPixel.h>
#define DS1307_ADDRESS 0x68

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(90, 9, NEO_GRB + NEO_KHZ800);

int second;
int minute;
int hour;


void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT); 
  pixels.begin();
  for(int i = 0; i<10;i++){
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

  }
  pixels.show();
}

void loop(){
  printDate();
  if(minute>=0){
    digitalWrite(3,HIGH);
  }
  else{
    digitalWrite(3,LOW);
  }
  if(minute>=15){
    digitalWrite(4,HIGH);
  }
  else{
    digitalWrite(4,LOW);
  }
  if(minute>=30){
    digitalWrite(5,HIGH);
  }
  else{
    digitalWrite(5,LOW);
  }
  if(minute>=45){
    digitalWrite(6,HIGH);
  }
  else{
    digitalWrite(6,LOW);
  }
 /* for(int i = 0; i<10;i++){
    if(i<=hour){
      pixels.setPixelColor(i, pixels.Color(50, 0, 255));
    }else{
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    }
  }*/
  pixels.show();
  Serial.println(hour);
}

byte bcdToDec(byte val)  {
  // Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());

  //print the date EG   3/1/11 23:59:59
  /* Serial.print(month);
   Serial.print("/");
   Serial.print(monthDay);
   Serial.print("/");
   Serial.print(year);
   Serial.print(" ");
   Serial.print(hour);
   Serial.print(":");
   Serial.print(minute);
   Serial.print(":");
   Serial.println(second);*/

}






