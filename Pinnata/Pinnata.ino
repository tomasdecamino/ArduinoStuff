//Arduino 1.0+ Only
//Arduino 1.0+ Only

#include "Wire.h"
#include <Adafruit_NeoPixel.h>
#define DS1307_ADDRESS 0x68

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(90, 6, NEO_GRB + NEO_KHZ800);

int second;
int minute;
int hour;

int time3  = 19;
int time2 = 17;
int time1 = 11;


void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(10,INPUT_PULLUP);
  digitalWrite(3,LOW);
  pixels.begin();
  for(int i = 0; i<90;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  }
  pixels.show();
}

void loop(){

  delay(500);
  printDate();
  Serial.println(hour);
  if(digitalRead(10)==0){
   digitalWrite(3,HIGH); 
  }else{
   digitalWrite(3,LOW); 
  }
  
  for(int i=90;i>=0;i--){
    if(hour>=time1){
      pixels.setPixelColor(i, pixels.Color(0, 255,0));
    }
    if(hour>=time2){
      pixels.setPixelColor(i, pixels.Color(255, 255,0));
    }
    if(hour>=time3){
      pixels.setPixelColor(i, pixels.Color(255, 0,0));
    }
    if(hour<time1){
      pixels.setPixelColor(i, pixels.Color(0, 0,255));
    }
    delay(100);
    pixels.show();
  }
  for(int i = 0; i<90;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  }
  pixels.show();

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




