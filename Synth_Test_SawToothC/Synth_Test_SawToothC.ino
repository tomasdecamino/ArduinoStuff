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

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (9)

/* Note: If flash space is tight a quarter sine wave is enough
   to generate full sine and cos waves, but some additional
   calculation will be required at each step after the first
   quarter wave.                                              */


void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");
  dac.begin(0x62);

  Serial.println("Generating a sine wave");
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
}

void loop(void) {
  float val = (float)analogRead(A0) / 1023;
  int val2 = map(analogRead(A3),0,1023,0,16000);
  // Push out the right lookup table, depending on the selected resolution
  int w = round((2047 * sin(TWO_PI * x) + 2047));
  dac.setVoltage(w, false);
//  Serial.println(w);
  x += val;
  delayMicroseconds(val2);
}
