/*Tomas de Camino Beck
www.funcostarica.org

*/
#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>
#include <Wire.h>
#include <SPI.h>

#define MAX 15000 //maximo de actividad

Servo servo;

int count = 0;

void setup() {
  // put your setup code here, to run once:
  servo.attach(2);
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  int mY = CircuitPlayground.motionY() ;
  int ang = map(mY,10,-10,0,180);
  servo.write(ang);
}

