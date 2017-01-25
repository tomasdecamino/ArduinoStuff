//Tomas de Camino Beck
//Reading from Adafruit SI1145
#include <Wire.h>
#include "Adafruit_SI1145.h"

Adafruit_SI1145 uv = Adafruit_SI1145();

void setup() {
  Serial.begin(9600);
  uv.begin();
}

void loop() {
  Serial.print(uv.readVisible());
  Serial.print(",");
  Serial.print(uv.readIR());
  Serial.print(",");
  Serial.println(uv.readUV());

  delay(200);
}
