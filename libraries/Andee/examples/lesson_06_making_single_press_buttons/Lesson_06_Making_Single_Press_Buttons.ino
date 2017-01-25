/************************************************************
  [Annikken Andee]
  ================
  Lesson 6
  Making Single-Press Buttons
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// In this lesson, you'll learn how to create a single-press button.
// Single-press buttons are useful if you wish to prevent accidental
// repeated button presses. For example, if you wish to create
// a button to send an SMS, you do not want to accidentally send 5
// SMSes if the user accidentally hits the button five times.
// Single-press buttons help to prevent these kinds of errors from
// happening.

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll create a display and a button to show you how to
// program a button to do something
AndeeHelper displaybox;
AndeeHelper button;

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Let's draw a display box!
  displaybox.setId(0);  // Each object must have a unique ID number
  displaybox.setType(DATA_OUT);  // This defines your object as a display box
  displaybox.setLocation(0, 0, FULL); 
  displaybox.setTitle("Single Press Buttons"); 
  displaybox.setData("Waiting for button press"); 
  
  button.setId(1); // Don't forget to assign a unique ID number
  button.setType(BUTTON_IN); // Defines object as a button
  button.setLocation(1,0,FULL);
  button.setTitle("Press me!");
  // Optional:
  button.requireAck(true);
  // By default this is already set to true to prevent accidental presses
  // after the first button press.
  
  // You can't use setData() and setUnit() for buttons.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // Here's how you code a single-press button action.
  if( button.isPressed() )
  {
    // Prevents a repeated button press. Button will not be available until Arduino
    // replies the smartphone with an acknowledgement message.
    button.ack(); 
    
    // Add action here!
    // In this example, pressing the button will change the text in the display box above
    displaybox.setData("Button has been pressed!"); 
  }
  
  displaybox.update(); // Don't forget to call update() or else your objects won't show up
  button.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



