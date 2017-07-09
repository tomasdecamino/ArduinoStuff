#include <Adafruit_CircuitPlayground.h>
uint8_t red, green, blue;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:


  if (CircuitPlayground.rightButton()) {
    CircuitPlayground.clearPixels();
    
    CircuitPlayground.senseColor(red, green, blue);
  }

  
  for (int i = 3; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(red, green, blue));
  }
   
}
