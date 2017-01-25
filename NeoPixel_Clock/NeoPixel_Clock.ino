//Arduino 1.0+ Only
//Arduino 1.0+ Only

#include "Wire.h"
#include <Adafruit_NeoPixel.h>
#define DS1307_ADDRESS 0x68

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);

  int second;
  int minute;
  int hour;

void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  pixels.begin();
}

void loop(){
  for(int i = 0; i<16;i++){
     pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    
  }
  printDate();
  Serial.println(16-map(second,0,59,1,16));
  pixels.setPixelColor(16-map(hour%12,0,11,1,16), pixels.Color(230, 144, 14));
  pixels.setPixelColor(16-map(minute,0,59,1,16), pixels.Color(16, 228, 213));
  pixels.setPixelColor(16-map(second,0,59,1,16), pixels.Color(255, 0, 255));
   // pixels.setPixelColor(16-map(3%12,0,11,1,16), pixels.Color(255, 0, 0));

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
