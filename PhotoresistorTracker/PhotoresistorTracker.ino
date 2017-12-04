
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 2, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(255,255, 255));
  pixels.show();
  pinMode(A0,INPUT);
}

void loop() {
  pixels.setPixelColor(1, pixels.Color(255,255, 255));
  pixels.show();
  Serial.println(analogRead(A0));
  
}

