/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

int count = 0;

void setup() {
  pinMode(A9, INPUT); //inicializa el pad para conectar un sensor
  CircuitPlayground.begin();//inicia el playground
}

void loop() {
  //lee el sensor y luego lo convierte a valores 0 a 255
  int val = map(analogRead(A9),0,1023,0,255);
  //contador % significa funcion modulo
  //cuenta hasta 10 para ir prediendo todos los leds
  count=(count+1)%10;
  //cambia color del led
  CircuitPlayground.setPixelColor(count, CircuitPlayground.colorWheel(val));
}

