#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(72, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(72, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(72, 9, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip.show();
  strip2.show();
  strip3.show();
  strip4.show();
  colorOne(strip.Color(0, 154, 205), 1000);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
 // rainbow(20);
 // rainbowCycle(20);
  //colorOne(strip.Color(150, (int)random(100,255), 255), 1000);
  delay(2000);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip2.setPixelColor(i, c);
    strip3.setPixelColor(i, c);
    strip4.setPixelColor(i, c);
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      strip2.setPixelColor(i, Wheel((i+j) & 255));
      strip3.setPixelColor(i, Wheel((i+j) & 255));
      strip4.setPixelColor(i, Wheel((i+j) & 255));
    }
   // strip.show();
    strip2.show();
    strip3.show();
   // strip4.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip3.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip4.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    //strip.show();
    strip2.show();
    //strip3.show();
    //strip4.show();
    delay(wait);
  }
}


void colorOne(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip2.setPixelColor(i, c);
    strip3.setPixelColor(i, c);
    strip4.setPixelColor(i, c);
  }
  //strip.show();
  strip2.show();
  strip3.show();
 // strip4.show();
  delay(wait);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}








