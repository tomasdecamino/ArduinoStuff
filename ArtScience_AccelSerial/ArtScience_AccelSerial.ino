/*Tomas de Camino Beck
  www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>

boolean on = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
}

void loop() {
  Serial.print(CircuitPlayground.motionX());
  Serial.print(",");
  Serial.print(CircuitPlayground.motionY());
  Serial.print(",");
  Serial.println(CircuitPlayground.motionZ());

}


