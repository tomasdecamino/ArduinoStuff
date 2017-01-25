#include <Wire.h>
#include <Adafruit_LSM303.h> //libreria de Adafruit

Adafruit_LSM303 lsm; //prepara el objeto

void setup()
{
  Serial.begin(9600);
  //inicializa el acelerometro
  lsm.begin();

}

void loop()
{
  lsm.read();//lee la informacion del sensor
  //manda la lectura a serial
  Serial.print((int)lsm.accelData.x); Serial.print(",");
  Serial.print((int)lsm.accelData.y); Serial.print(",");
  Serial.println((int)lsm.accelData.z);
  delay(50);
}
