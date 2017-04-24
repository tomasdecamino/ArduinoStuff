/* @author: Alex Roberto Vargas Benamburg
 * April 2016
 * www.funcostarica.org

Made for teaching poruposes www.funcostarica.org
Released under MIT License
Copyright (c) 2016  Alex Roberto Vargas Benamburg
 */

#include "RobotKit.h"

const int ledPin = 8;

//Variables para cada canal de color.
int colorRojo = 0;
int colorVerde = 0;
int colorAzul = 0;

//Direccion de cada canal
int direccionR = 1; // 1 = incremento
int direccionV = 1; // -1 = decremento
int direccionA = 1;

void setup(){
  startLED(ledPin);
}

void loop(){
  setLED(colorRojo,colorVerde,colorAzul);
  delay(100);

  colorRojo = colorRojo + (random(1,25)*direccionR);
  colorVerde = colorVerde + (random(1,25)*direccionV);
  colorAzul = colorAzul + (random(1,25)*direccionA);

  if(colorRojo>255){
    direccionR = -1;
    colorRojo = 255;
  }
  if(colorAzul>255){
    direccionA = -1;
    colorAzul = 255;
  }
  if(colorVerde>255){
    direccionV = -1;
    colorVerde = 255;
  }

  if(colorRojo<0){
    direccionR = 1;
    colorRojo = 0;
  }
  if(colorVerde<0){
    direccionV = 1;
    colorVerde = 0;
  }
  if(colorAzul<0){
    direccionA = 1;
    colorAzul = 0;
  }
}
