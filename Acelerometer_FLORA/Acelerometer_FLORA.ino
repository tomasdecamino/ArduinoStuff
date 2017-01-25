#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup() 
{
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  lsm.read();
  Serial.print((int)lsm.accelData.x);Serial.print(",");
  Serial.print((int)lsm.accelData.y);Serial.print(",");
 Serial.println((int)lsm.accelData.z);
  delay(100);
}
