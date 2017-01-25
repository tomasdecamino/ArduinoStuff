/************************************************************
  [Annikken Andee]
  ================
  Rubber Band Launcher
  by Jonathan Sim <jonathan@annikken.com>

  The Rubber Band Launcher makes use of 3x servos. One 
  controls the firing and reload mechanism, while the other 
  two controls the horizontal and vertical direction of the 
  launcher.

  You can easily build this by cutting up four pairs of 
  chopsticks and by tying everything up using rubber bands! 
  To mount the base servo, just cut off the top of a 1.5L 
  plastic soda bottle and tape that to a base. The mouth piece 
  is just the  right size to hold the base servo in place.
 
  Try it! It'll be lots of fun!
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

#include <SPI.h>
#include <Andee.h>
#include <Servo.h>

#define TURN 5
#define TURNANTICLOCK -1
#define TURNCLOCK 1

// These are all the objects that we'll have on our screen
AndeeHelper btnFire;
AndeeHelper btnUp;
AndeeHelper btnDown;
AndeeHelper displayStatus;
AndeeHelper btnReset;
AndeeHelper btnposA;
AndeeHelper btnposMoveX;
AndeeHelper btnposMoveY;
AndeeHelper btnLeft;
AndeeHelper btnRight;
AndeeHelper btnStop;
Servo servoVERT; // The three servos
Servo servoHORZ;
Servo servoFire;
int posHORZ = 0; // Variables to store the position of our servos
int posVERT = 0;
int pos;
char input[3];
char temp[10];
int x = 999;
int y = 999;

// Our servos will be connected to pins 2, 3, and 4.
int pinFIRE = 2;
int pinservoVERT = 3;
int pinservoHORZ = 4;


void setup()
{
  Andee.begin();
  Andee.clear();
  setInitialData();
  
  // Tell Arduino where the servos are attached
  servoFire.attach(pinFIRE);
  servoVERT.attach(pinservoVERT);
  servoHORZ.attach(pinservoHORZ);
  
  // Initialise launcher to start up at a particular position
  // We're turning our servos slowly so that the momentum of the swing will
  // not be too great to make the launcher lose its balance.
  for(posVERT = 90; posVERT > 45; posVERT--)  
  { 
    servoVERT.write(posVERT); 
    delay(10); 
  }
  for(posHORZ = 0; posHORZ < 90; posHORZ++)   
  {
    servoHORZ.write(posHORZ);  
    delay(10);     
  }  
  fire();
  btnFire.setTitle("FIRE"); 
}

// This is where we draw all our screen objects
void setInitialData()
{
  displayStatus.setId(0);
  displayStatus.setType(DATA_OUT);
  displayStatus.setTitle("Rubber Band Launcher Mark II");
  displayStatus.setData("Initialising...");
  displayStatus.setLocation(0,1,FULL);
  displayStatus.setTitleColor(BLACK);
  displayStatus.setColor(BLACK);  

  btnReset.setId(1);
  btnReset.setType(BUTTON_IN);
  btnReset.setTitle("");
  btnReset.setLocation(1,0,ONE_THIRD);
  btnReset.setColor(DKGRAY);

  btnUp.setId(2);
  btnUp.setType(BUTTON_IN);
  btnUp.setTitle("UP");
  btnUp.setLocation(1,1,ONE_THIRD); 
  btnUp.setColor(GRAY);
  btnUp.requireAck(false); // You need this line to allow for multiple button presses

  btnposA.setId(3);
  btnposA.setType(BUTTON_IN);
  btnposA.setTitle("Save Position");
  btnposA.setLocation(1,2,ONE_THIRD);
  btnposA.setColor(DKGRAY); 

  btnLeft.setId(4);
  btnLeft.setType(BUTTON_IN);
  btnLeft.setTitle("LEFT");
  btnLeft.setLocation(2,0,ONE_THIRD); 
  btnLeft.setColor(GRAY);
  btnLeft.requireAck(false); // You need this line to allow for multiple button presses

  btnFire.setId(5);
  btnFire.setType(BUTTON_IN);
  btnFire.setTitle("FIRE");
  btnFire.setLocation(2,1,ONE_THIRD);
  btnFire.setColor(RED);  

  btnRight.setId(6);
  btnRight.setType(BUTTON_IN);
  btnRight.setTitle("RIGHT");
  btnRight.setLocation(2,2,ONE_THIRD); 
  btnRight.setColor(GRAY);  
  btnRight.requireAck(false); // You need this line to allow for multiple button presses

  btnposMoveX.setId(7);
  btnposMoveX.setType(KEYBOARD_IN);
  btnposMoveX.setKeyboardType(ANDROID_NUMERIC);
  btnposMoveX.setTitle("Move X-axis");
  btnposMoveX.setLocation(3,0,ONE_THIRD);
  btnposMoveX.setColor(DKGRAY);

  btnDown.setId(8);
  btnDown.setType(BUTTON_IN);
  btnDown.setTitle("DOWN");
  btnDown.setLocation(3,1,ONE_THIRD);
  btnDown.setColor(GRAY);
  btnDown.requireAck(false); // You need this line to allow for multiple button presses

  btnposMoveY.setId(9);
  btnposMoveY.setType(KEYBOARD_IN);
  btnposMoveY.setKeyboardType(ANDROID_NUMERIC);
  btnposMoveY.setTitle("Move Y-axis");
  btnposMoveY.setLocation(3,2,ONE_THIRD);
  btnposMoveY.setColor(DKGRAY);
}

// Function to move launcher downwards
void turnDown()
{
  int newPos = posVERT + TURN;
  if(newPos > 90) newPos = 90;
  for(posVERT; posVERT < newPos; posVERT++)  
  { 
    servoVERT.write(posVERT); 
    delay(10);
  } 
}

// Function to move launcher downwards by a user-specified amount
void turnDown(int newPos)
{
  if(newPos > 90) newPos = 90;
  for(posVERT; posVERT < newPos; posVERT++) 
  {   
    servoVERT.write(posVERT);
    delay(10);
  } 
}

// Function to move launcher upwards
void turnUp()
{
  int newPos = posVERT - TURN;
  if(newPos < 0) newPos = 0;
  for(posVERT; posVERT > newPos; posVERT--)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoVERT.write(posVERT);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}

// Function to move launcher upwards by a user-specified amount
void turnUp(int newPos)
{

  if(newPos < 0) newPos = 0;
  for(posVERT; posVERT > newPos; posVERT--) 
  {    
    servoVERT.write(posVERT);    
    delay(10);
  } 
}


// Function to move launcher left
void turnLeft()
{
  int newPos = posHORZ - TURN;
  if(newPos < 0) newPos = 0;
  for(posHORZ; posHORZ > newPos; posHORZ--) 
  { 
    servoHORZ.write(posHORZ); 
    delay(10); 
  } 
}

// Function to move launcher left by a user-specified amount
void turnLeft(int newPos)
{
  if(newPos < 0) newPos = 0;
  for(posHORZ; posHORZ > newPos; posHORZ--)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoHORZ.write(posHORZ);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}

// Function to move launcher right
void turnRight()
{
  int newPos = posHORZ + TURN;
  if(newPos > 180) newPos = 180;
  for(posHORZ; posHORZ < newPos; posHORZ++)   
  { 
    servoHORZ.write(posHORZ);
    delay(10);  
  } 
}

// Function to move launcher right by a user-specified amount
void turnRight(int newPos)
{
  if(newPos > 180) newPos = 180;
  for(posHORZ; posHORZ < newPos; posHORZ++)   
  {         
    servoHORZ.write(posHORZ);     
    delay(10);  
  } 
}

// Function to fire the rubber band
void fire()
{
  for(pos = 115; pos > 45; pos--) // Goes down to fire
  { 
    servoFire.write(pos);  
    delay(5); 
  }  
  for(pos = 45; pos < 180; pos++) // Goes backwards to reload
  {                            
    servoFire.write(pos);    
    delay(5);    
  }
  for(pos = 180; pos > 115; pos--)  // Goes to wait position
  {  
    servoFire.write(pos); 
    delay(5);           
  }   
}

// Function to decide whether to move up or down when user sets a value
void moveY(int y_pos)
{
  if(y_pos > posVERT)
    turnDown(y_pos);
  else
    turnUp(y_pos);
}

// Function to decide whether to move left or right when user sets a value
void moveX(int x_pos)
{
  if(x_pos > posHORZ)
    turnRight(x_pos);
  else
    turnLeft(x_pos);
}

void loop()
{
  if(Andee.isConnected()) // Draw the objects on screen once upon connection
  {
    btnFire.update();
    btnUp.update();
    btnDown.update();
    displayStatus.update();
    btnposA.update();
    btnReset.update();
    btnposMoveX.update();
    btnposMoveY.update();
    btnLeft.update();
    btnRight.update();
  }
  
  // Button actions
  if(btnFire.isPressed())
  {
    btnFire.ack();
    fire();
  }
  if(btnposMoveY.isPressed())
  {
    btnposMoveY.getKeyboardMessage(input);
    btnposMoveY.ack();
    moveY(atoi(input));
    memset(input,0x00, 3);
  }
  if(btnposMoveX.isPressed())
  {
    btnposMoveX.getKeyboardMessage(input);
    btnposMoveX.ack();
    moveX(atoi(input));
    memset(input,0x00, 3);
  }  
  if(btnUp.getButtonPressCount() > 0)
  {
    turnUp();
  }
  if(btnDown.getButtonPressCount() > 0)
  {
    turnDown();
  }
  if(btnLeft.getButtonPressCount() > 0)
  {
    turnLeft();
  }
  if(btnRight.getButtonPressCount() > 0)
  {
    turnRight();
  }
  
  // Button action when "Save and Fire" button has no saved position
  if(x == 999 && btnposA.isPressed())
  {
    btnposA.ack();
    sprintf(temp, "Move to (%d,%d) and fire", posHORZ, posVERT);
    x = posHORZ;
    y = posVERT;
    btnposA.setTitle(temp);
    btnReset.setTitle("Reset Saved Position");
    btnposA.update();
    btnReset.update();    
  }
  
  // Button action when "Save and Fire" button has a saved position
  if(x != 999 && btnposA.isPressed())
  {
    btnposA.ack();
    moveX(x);
    moveY(y);
    fire();
  }
  
  if(btnReset.isPressed())
  {
    btnReset.ack();
    x = 999;
    y = 999;
    btnposA.setTitle("Save Position");
    btnReset.setTitle("");
    btnposA.update();
    btnReset.update();
  }
  
  // Display updated status of the launcher
  sprintf(temp, "X:%d Y:%d", posHORZ, posVERT);
  displayStatus.setData(temp);
  displayStatus.update();
  delay(500);
}



