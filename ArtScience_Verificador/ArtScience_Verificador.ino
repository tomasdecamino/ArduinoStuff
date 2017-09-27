#include <Adafruit_CircuitPlayground.h>
uint8_t red, green, blue;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int sum= digitalRead(2)+digitalRead(3)+digitalRead(9)+digitalRead(10);

  red=green=blue=0;
  if(sum>=2) green=255;
  else red=255;
  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(red, green, blue));
  }
  delay(100);

}
