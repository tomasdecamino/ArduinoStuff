/*Tomas de Camino Beck
  www.funcostarica.org
  //Simple medidor de temperatura
*/
#include <Adafruit_CircuitPlayground.h>

//Rango de temperaturas que marcan los LEDs
#define MIN 20
#define MAX 1023

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}


void loop() {
  
  float temp = CircuitPlayground.lightSensor();
  pixelMeter(temp,MIN,MAX);
}

void pixelMeter(float value, float minimum, float maximum){
  int p = map(value,minimum,maximum,0,9);
  CircuitPlayground.clearPixels();
  for(int i=0;i<=p;i++){
    int c=map(i,0,9,0,255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(c,255-c,0));
  }
}

