/************************************************************
  [Annikken Andee]
  ================
  Lesson 7
  Making a Toggle Button
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

/* A toggle button is a button that changes between two states
  when pressed, e.g. On and off. */

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll just create one button to toggle
AndeeHelper togglebutton;

int state; // This variable will store the current state

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  state = 0; // Initialise your state to zero
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Let's draw a toggle button
  togglebutton.setId(0); // Don't forget to assign a unique ID number
  togglebutton.setType(BUTTON_IN); // Defines object as a button
  togglebutton.setLocation(0,0,FULL);
  togglebutton.setTitle("Turn On"); // Sets the initial words for button
  togglebutton.setColor(GREEN);
  // You can't use setData() and setUnit() for buttons.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // Here's how you code the button action
  if( togglebutton.isPressed() )
  {
    // Prevent user from accidentally pressing the button again
    // until Arduino has sent an acknowledgement 
    togglebutton.ack(); 
    
    if(state == 0)
    {
      togglebutton.setTitle("Turn off");
      state = 1; // Change state 
      togglebutton.setColor(RED);   
      // Add additional actions here to turn on something
    }
    else
    {
      togglebutton.setTitle("Turn on");
      state = 0; // Change state 
      togglebutton.setColor(GREEN); 
      // Add additional actions here to turn off something
    }  
  }
  
  togglebutton.update(); // Update your button to reflect the change in state

  delay(500); // Always leave a short delay for Bluetooth communication
}



