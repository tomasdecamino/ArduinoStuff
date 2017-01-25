#include <Andee.h>
#include <SPI.h>

//in iOS, you have can have rectangular or circle buttons.
AndeeHelper buttonRect;
AndeeHelper buttonCircle;

void setup(){
  Andee.begin();
  Andee.clear();
 
  buttonRect.setId(0);
  buttonRect.setType(BUTTON_IN);
  buttonRect.setLocation(0,0, FULL);
  buttonRect.setTitle("Rectangular");
  //buttonRect.setColor(GREEN);
  
  buttonCircle.setId(1);
  buttonCircle.setType(CIRCLE_BUTTON);
  buttonCircle.setLocation(1,0, FULL);
  buttonCircle.setTitle("Circle");
  //buttonCircle.setColor(GREEN);
}

void loop(){
  //Show buttons on screen
  buttonRect.update();
  buttonCircle.update();
  
  //Handle if buttonRect is pressed.
  if(buttonRect.isPressed(1)){
    buttonRect.ack();
  }
  
  //Handle if buttonCircle is pressed.
  if(buttonCircle.isPressed()){
    buttonCircle.ack();
  }
  delay(200);
}
