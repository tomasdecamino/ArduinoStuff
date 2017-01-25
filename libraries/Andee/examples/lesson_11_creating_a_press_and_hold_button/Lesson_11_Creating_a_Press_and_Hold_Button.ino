/************************************************************
  [Annikken Andee]
  ================
  Lesson 11
  Creating a Press-and-Hold Button
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// Sometimes, you may wish to press and hold a button to repeat
// a certain action instead of constantly pressing the button.
// This lesson will teach you all you need to know to do this!

// To demonstrate this, we'll connect an LED and have the LED 
// flash repeatedly as long as the button is constantly pressed

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll create a display and a button to show you how to
// program a button to do something
AndeeHelper displaybox;
AndeeHelper button;

const int pinLED = 2; // Set LED pin to output pin 2

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  pinMode(pinLED, OUTPUT); // Configures pin 2 for output.
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Let's draw a display box!
  displaybox.setId(0);  // Each object must have a unique ID number
  displaybox.setType(DATA_OUT);  // This defines your object as a display box
  displaybox.setLocation(0, 0, FULL); 
  displaybox.setTitle("Press-and-Hold Button"); 
  displaybox.setData("Press and hold to make the LED blink continuously!"); 
  
  button.setId(1); // Don't forget to assign a unique ID number
  button.setType(BUTTON_IN); // Defines object as a button
  button.setLocation(1,0,FULL);
  button.setTitle("Press me!");
  button.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{ 
  // Here's how you code a press-and-hold button:
  if( button.getButtonPressCount() > 0 ) // Do this as long as the button is pressed
  {
    // Add your press and hold action here:
    digitalWrite(pinLED, HIGH);
    delay(500);
    digitalWrite(pinLED, LOW);
  }
  
  displaybox.update(); // Don't forget to call update() or else your objects won't show up
  button.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



