#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;


void setup() 
{
  Serial.begin(9600);
  if (!lsm.begin())
  {
    Serial.println("problemas inicializando el LSM303");
    while (1);
  }
}

void loop() 
{
  
  lsm.read();
  Serial.print((int)lsm.accelData.x);     
  Serial.print(",");
  Serial.print((int)lsm.accelData.y);
  Serial.print(",");
  Serial.println((int)lsm.accelData.z);
  delay(100);
}
