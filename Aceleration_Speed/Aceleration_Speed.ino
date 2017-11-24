/*Tomas de Camino Beck
  www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>

boolean on = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  if (CircuitPlayground.slideSwitch()) {
    Serial.print(CircuitPlayground.motionX());
    Serial.print(",");
    Serial.print(CircuitPlayground.motionY());
    Serial.print(",");
    Serial.print(CircuitPlayground.motionZ());
    Serial.print(",");
    Serial.println(micros());
  }else{
    Serial.println("**");
  }
 delay(100);

}

