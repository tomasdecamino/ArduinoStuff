//Tomas de Camino Beck
//Polymathboxes

#include <Wire.h>
#include <Adafruit_MCP4725.h>


Adafruit_MCP4725 dac;

float x = 0;

#define POT1 A0
#define POT2 A1

void setup(void) {
  Serial.begin(9600);
  dac.begin(0x62);

  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
}

void loop(void) {
  float val = (float)analogRead(POT2) / 1023;
  int val2 = map(analogRead(POT1),0,1023,1,16000);
  // Push out the right lookup table, depending on the selected resolution
  int w = round((2047 * sin(TWO_PI * x) + 2047));
  dac.setVoltage(w, false);
  Serial.println(w);
  x += val;
  delayMicroseconds(val2);
}
