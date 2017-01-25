#include <Andee.h>
#include <SPI.h>

AndeeHelper analogDial;
int current; //dial's current value
const int minValue = 0; //dial's min value
const int maxValue = 100; //dial's max value

void setup(){
  Andee.begin();
  Andee.clear();
  
  analogDial.setId(0);
  analogDial.setType(ANALOG_DIAL_OUT);
  analogDial.setLocation(0,0,FULL);
  
  //Values can be double/float.
  //E.g. analogDial.setMinMax(0.1, 100.1);
  analogDial.setMinMax(minValue, maxValue);
  
  analogDial.setTitle("Analog dial");
  
  //These functions set different colors to the dial
  //analogDial.setMainColor(MEDIUM_SEA_GREEN); 
  //analogDial.setSubColor(FORREST_GREEN);
  
  current = 0; //Let's start dial at value = 0
  analogDial.setData(current);
  
  analogDial.update(); //show dial on screen
  
}

void loop(){
  
  analogDial.updateData(current++);
  
  //This branch resets dial's value to min when it reaches max
  if(current >= maxValue){
    current = minValue;
  }
  
  delay(200);
}
