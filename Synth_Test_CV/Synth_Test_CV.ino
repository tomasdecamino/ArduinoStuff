/**************************************************************************/
/*!
    @file     sinewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a sine wave with the MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

float x = 0;



void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");
  dac.begin(0x62);

  Serial.println("Generating a sine wave");
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
}

void loop(void) {
  float val = map(analogRead(A0),0,1023,0,4095);
  // Push out the right lookup table, depending on the selected resolution
  dac.setVoltage(val, false);
}
