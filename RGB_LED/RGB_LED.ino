
#include <Adafruit_NeoPixel.h>

// pin donde estan conectados
#define PIN 6

// numero de LEds
#define NUM 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin(); // inica la libreria
}

void loop() {
  
  for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(150,150,0)); // 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(300); 
  }
}
