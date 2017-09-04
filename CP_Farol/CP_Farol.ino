#include <Adafruit_CircuitPlayground.h>
uint8_t red, green, blue;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:



  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255, 0, 0));
    delay(200);
  }
  delay(2000);
  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(0, 0, 255));
    delay(200);
  }
  delay(2000);
  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255, 255, 255));
  delay(200);
  }
  delay(2000);
}
