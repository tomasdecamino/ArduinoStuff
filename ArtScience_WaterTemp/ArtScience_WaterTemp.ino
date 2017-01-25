/*creado por Tomas de Camino Beck
www.funcostarica.org
*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
//define el maximo y minimo de lectura del sensor
#define MIN 330
#define MAX 1023


void setup() {
  // put your setup code here, to run once:
  pinMode(A9,INPUT);
  Serial.begin(9600);
  //inicial el playground
  CircuitPlayground.begin();
}

void loop() {
  // lee el sensor y lo almacena en la variable val
  int val = analogRead(A9);
  Serial.print(val);
  Serial.print(",");
  Serial.println(CircuitPlayground.temperature());
  // muestra la lectura en los pixeles
  pixelMeter(val,MIN,MAX);
  delay(60000); //lee datos cada minuto
}


//c'odigo para usar los leds como medidor
void pixelMeter(float value, float minimum, float maximum){
  int p = map(value,minimum,maximum,0,10);
  CircuitPlayground.clearPixels();
  for(int i=0;i<=p;i++){
    int c=map(i,0,9,0,255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.strip.Color(255,0,0));
  }
}
