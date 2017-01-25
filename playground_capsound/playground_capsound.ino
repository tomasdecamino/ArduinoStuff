/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>


void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}


void loop() {

  int val = map(CircuitPlayground.readCap(10),0,255,100,400);
  CircuitPlayground.playTone(val,10);

}
