/************************************************************
  [Annikken Andee]
  ================
  Lesson 13
  Using Buttons to Control Servos
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>
#include <Servo.h> 

// We'll create 3 buttons. One to make it slowly turn left, the other
// to make it slowly turn right. And the third one to quickly turn to
// a user-specified position. We'll also create one display box to tell
// us about the servo's current position
AndeeHelper btnTurnLeft;
AndeeHelper btnTurnRight;
AndeeHelper btnCustomPosition;
AndeeHelper displaybox;

Servo theServo; // Declare a servo

char userPos[4];
int currentPosition; // Stores current position of servo (from 0 to 180)
int newPosition;
int turnResolution = 10; // Servo turns by 20 every time left/right turn button is pressed
const int servoPin = 2; // Servo connected to pin 2

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  currentPosition = 0; // Initialise position to 0
  theServo.attach(servoPin); // Tell Arduino which pin the servo is connected to
  theServo.write(currentPosition); // Set servo to position 0
  setInitialData(); // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  btnTurnLeft.setId(0);
  btnTurnLeft.setType(BUTTON_IN);
  btnTurnLeft.setLocation(0,0,HALF);
  btnTurnLeft.setTitle("Turn Left");
  btnTurnLeft.requireAck(false); // You need this line to allow for multiple button presses
  
  btnTurnRight.setId(1);
  btnTurnRight.setType(BUTTON_IN);
  btnTurnRight.setLocation(0,1,HALF);
  btnTurnRight.setTitle("Turn Right");
  btnTurnRight.requireAck(false); // You need this line to allow for multiple button presses  
  
  btnCustomPosition.setId(2);
  btnCustomPosition.setType(KEYBOARD_IN); // Sets object as a text input button
  btnCustomPosition.setLocation(1,0,FULL);
  btnCustomPosition.setTitle("Quickly Go to Custom Position (0 - 180)");
  btnCustomPosition.setKeyboardType(ANDEE_NUMERIC_A); 

  displaybox.setId(3);
  displaybox.setType(DATA_OUT); // Sets object as a text input button
  displaybox.setLocation(2,0,FULL);
  displaybox.setTitle("Current Position");
  displaybox.setData(0);
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( btnCustomPosition.isPressed() )
  {
    memset(userPos, 0x00, 4); // Empty the contents of the string before receiving user input
    btnCustomPosition.ack(); // Acknowledge button press or else phone will be left waiting
    btnCustomPosition.getKeyboardMessage(userPos); // Display keyboard and store input into userInput

    newPosition = atoi(userPos); // Convert string value to integer value
    
    // Tell Arduino x Andee what to do if user keys in ridiculous values
    if(newPosition < 0) newPosition = 0;
    if(newPosition > 180) newPosition = 180;
    
    currentPosition = newPosition;
    // This is how you do a quick turn
    theServo.write(currentPosition); // Turn servo to new position
    displaybox.setData(currentPosition); // Update new position
  }
  
  if( btnTurnLeft.getButtonPressCount() > 0 ) // As long as left button is pressed
  {
    btnTurnLeft.ack(); // Acknowledge button press or else phone will be left waiting
    newPosition = currentPosition - turnResolution; // Set new position
    if(newPosition < 0) newPosition = 0; // Set to 0 if new position goes below 0
    
    // This is how you do a slow turn:
    for(currentPosition; currentPosition > newPosition; currentPosition--)
    {
      theServo.write(currentPosition);
      displaybox.setData(currentPosition); // Update servo position on screen as it turns
      displaybox.update();
      delay(15); // You can change the delay value. Larger value means slower turns
      // Do not set your delay to 0 when you're doing this. You run the possibility of 
      // damaging the servo. Or you might just make it become more cranky.
    }
  }  
  
  if( btnTurnRight.getButtonPressCount() > 0 ) // As long as right button is pressed
  {
    btnTurnRight.ack(); // Acknowledge button press or else phone will be left waiting
    newPosition = currentPosition + turnResolution; // Set new position
    if(newPosition > 180) newPosition = 180; // Set to 180 if new position goes above 180
    for(currentPosition; currentPosition < newPosition; currentPosition++)
    {
      theServo.write(currentPosition);
      displaybox.setData(currentPosition); // Update servo position on screen as it turns
      displaybox.update();
      delay(15); // You can change the delay value. Larger value means slower turns
    }
  }    
  
  btnTurnLeft.update(); // Always remember to update so that new content will be displayed
  btnTurnRight.update();
  btnCustomPosition.update();
  displaybox.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



