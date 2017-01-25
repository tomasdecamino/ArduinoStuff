//max Y 22000
//max X 28000

#include <AccelStepper.h>

// The X Stepper pins
#define STEPPER1_DIR_PIN 3
#define STEPPER1_STEP_PIN 2
// The Y stepper pins
#define STEPPER2_DIR_PIN 7
#define STEPPER2_STEP_PIN 6

int pX=14000;
int pY = 11000;
int count=0;

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);

void setup()
{  
  Serial.begin(9600);
  //Y dos motores
  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(1000.0);
  stepper1.moveTo(1000);
  //X carro
  stepper2.setMaxSpeed(2000.0);
  stepper2.setAcceleration(1000.0);
  stepper2.moveTo(1000);
  pinMode(4,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);    
  //busca el cero X
  while(digitalRead(4)==1){
    stepper2.setSpeed(1000);
    stepper2.runSpeed();
  }
  //Serial.println(digitalRead(4));
  stepper2.stop();
  stepper2.setCurrentPosition(28000);
  //Serial.println(digitalRead(8));
  //busca el 0 Y
  while(digitalRead(8)==1){
    //Serial.println(digitalRead(8));
    stepper1.setSpeed(-1000);
    stepper1.runSpeed();
  }
  //Serial.println(digitalRead(8));
  stepper1.stop();
  stepper1.setCurrentPosition(0);

}

void loop()
{
  // Change direction at the limits
  /* if (stepper1.distanceToGo() == 0)
   	stepper1.moveTo(-stepper1.currentPosition());
   if (stepper2.distanceToGo() == 0)
   	stepper2.moveTo(-stepper2.currentPosition());
   //stepper1.run();*/
  //stepper2.moveTo(0);
  //stepper2.run();
  if (stepper1.distanceToGo() == 0)
  {
    stepper1.moveTo(pY);
    pY+=cos(count)*3000;
    if(pY>21000||pY<1000)pY=11000;
  }

  if (stepper2.distanceToGo() == 0)
  {
    stepper2.moveTo(pX);
    pX+=cos(count)*3000;
    if(pX>27000||pX<1000)pX=14000; 
  }
  stepper1.run(); 
  stepper2.run(); 

}

