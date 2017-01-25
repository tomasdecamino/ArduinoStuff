#include <SPI.h> // These are the essential libraries you need
#include <Andee.h>
#include <Servo.h> 

AndeeHelper displayA; // Declare instances
AndeeHelper buttonA;
boolean isOn=false;
Servo myservo;
Servo myservo2;

void setup()
{
  Andee.begin(); // Sets up the communication link between Arduino and the Annikken Andee
  setInitialData();
  Andee.clear(); // Clear the screen of any previous displays
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  myservo.attach(9);
  myservo.write(90);
  myservo2.attach(10);
  myservo2.write(90);
  
}

void setInitialData()
{
  displayA.setId(0);
  displayA.setType(DATA_OUT);
  displayA.setLocation(0,0,FULL);
  displayA.setTitle("Servo");
  displayA.setData("0");
  displayA.setUnit("Position");

  buttonA.setId(1);
  buttonA.setType(BUTTON_IN);
  buttonA.setLocation(1,0,FULL);
  buttonA.setTitle("Prender");

} 

void loop()
{
  displayA.update();
  buttonA.update();
  if(buttonA.isPressed()){
    isOn=!isOn;
    displayA.setData("0");
    buttonA.ack();
  }
  if(isOn) {
    myservo.write(115);
    myservo2.write(105);
    displayA.setData("180");
  }
  else{
    myservo.write(60);
    myservo2.write(70);
  }
  delay(100);// Refresh displays every second
}


