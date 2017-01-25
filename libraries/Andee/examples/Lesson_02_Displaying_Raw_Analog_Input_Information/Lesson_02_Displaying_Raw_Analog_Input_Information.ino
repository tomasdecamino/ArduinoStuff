/************************************************************
  [Annikken Andee]
  ================
  Lesson 2
  Displaying Raw Analog Input Information
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// Works with any sensor. You can use the Light Dependent Resistor
// to try this out!

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll creating one object to display the analog input signal
AndeeHelper analogDisplay;

// We'll use Analog Input Pin A0 to read our analog input.
// Change the pin number if you are using another pin.
const int analogInputPin = A0;

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
  // Only one display box this time
  analogDisplay.setId(0);  // Each object must have a unique ID number
  analogDisplay.setType(DATA_OUT);  // This defines your object as a display box
  analogDisplay.setLocation(0, 0, FULL); // Sets the location and size of your object
  analogDisplay.setTitle("Analog Reading");
  analogDisplay.setData(""); // We'll update it with new analog data later.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // Read value from analog pin and store it in an int variable
  int reading = analogRead(analogInputPin); 
  analogDisplay.setData(reading); // Set the display box with new data value
  analogDisplay.update(); // Update the display to show the new value
  
  // A short delay is necessary to give Andee time to communicate with the smartphone
  delay(500); 
}

// FUN FACT! Did you know that if you press and hold on the display box, your phone will
// draw a graph?


