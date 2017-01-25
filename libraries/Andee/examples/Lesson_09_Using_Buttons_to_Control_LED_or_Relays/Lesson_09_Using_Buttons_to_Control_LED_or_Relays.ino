/************************************************************
  [Annikken Andee]
  ================
  Lesson 9
  Using Buttons to Control LED or Relays
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

/* The same code can be used to control both LEDs and Relays */

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll just create one button to toggle
AndeeHelper displayState;
AndeeHelper togglebutton;

// Connect LED/Relay to Pin 2
// Do not use Pins 8, 11, 12, 13 (Arduino Uno layout) as Andee 
// is using them. Strange things will happen if you do.
const int outputPin = 2;

int state; // This variable will store the current state

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  state = 0; // Initialise your state to zero
  
  pinMode(outputPin, OUTPUT); // Configures outputPin for output.
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // We're gonna create two objects. The first object, displayState, will
  // read the current state of the pin and report it to your smartphone.
  // The second object, togglebutton, will be used to turn the LED/relay
  // on or off.
  
  displayState.setId(0);// Don't forget to assign a unique ID number
  displayState.setType(DATA_OUT);
  displayState.setLocation(0,0,FULL);
  displayState.setTitle("Current Output State");
  
  togglebutton.setId(1); // Don't forget to assign a unique ID number
  togglebutton.setType(BUTTON_IN); // Defines object as a button
  togglebutton.setLocation(1,0,FULL);
  togglebutton.setTitle("Switch to HIGH"); // Sets the initial words for button
  // You can't use setData() and setUnit() for buttons.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{  
  state = digitalRead(outputPin); // Read current state of the output pin
  
  // Change text in the display box to indicate the current state of the pin
  if(state == 0) // LOW state
  {
    displayState.setData("LOW"); 
  }
  else // HIGH state
  {
    displayState.setData("HIGH");
  }
  
  // Here's how you code the button action
  if( togglebutton.isPressed() )
  {
    togglebutton.ack(); // Acknowledge button press. You must put this or your phone will be waiting
    
    if(state == 0) // If in a LOW state
    {
      togglebutton.setTitle("Switch to LOW");
      digitalWrite(outputPin, HIGH);
    }
    else // If in a HIGH state
    {
      togglebutton.setTitle("Switch to HIGH");
      digitalWrite(outputPin, LOW);
    }  
  }  

  displayState.update(); // Update new info onto smartphone screen 
  togglebutton.update(); 

  delay(500); // Always leave a short delay for Bluetooth communication
}



