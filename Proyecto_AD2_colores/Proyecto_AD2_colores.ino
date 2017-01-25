#include <Adafruit_NeoPixel.h>
#define PIN 6
#define TIME 3000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colores[9] = {
  strip.Color(255, 7, 0),
  strip.Color(224, 218, 6),
  strip.Color(5, 25, 255),
  strip.Color(232, 93, 9),
  strip.Color(0, 125, 19),
  strip.Color(255, 255, 255),
  strip.Color(255, 60, 255),//cambiar
  strip.Color(237, 124, 135),
  strip.Color(99, 241, 252),
};

boolean sensorPin[6]={
  false,false,false,false,false,false};

uint32_t color1 = strip.Color(255, 77, 103);
uint32_t color2 = strip.Color(247, 227, 6);


void setup() {
  pinMode(6,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A0,OUTPUT);

  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);  
  digitalWrite(A0,LOW);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  uint32_t color=colores[(int)random(0,8)];
  setColor(color);
  delay(650);
  Serial.println( digitalRead(2)); 
  if(digitalRead(2)==LOW){
    digitalWrite(9,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  if(digitalRead(3)==LOW){
    digitalWrite(10,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  if(digitalRead(4)==LOW){
    digitalWrite(11,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  if(digitalRead(5)==LOW){
    digitalWrite(12,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  if(digitalRead(7)==LOW){
    digitalWrite(13,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  if(digitalRead(8)==LOW){
    digitalWrite(A0,HIGH);
    //colorWipe(strip.Color(247, 227, 6),4); // Red
    delay(TIME);
  }
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);  
  digitalWrite(A0,LOW);


}



void setColor(uint32_t c){
  for(int i=0; i< strip.numPixels();i++){
    strip.setPixelColor(i,c);
  } 
  strip.show();
}








