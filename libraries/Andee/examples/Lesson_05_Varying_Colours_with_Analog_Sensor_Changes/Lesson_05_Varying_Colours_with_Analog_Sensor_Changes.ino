/************************************************************
  [Annikken Andee]
  ================
  Lesson 5
  Varying Colours with Analog Sensor Changes
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// For more information about available colour options, please
// refer to Lesson 4 Changing Colours.

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// We'll create a display to show you how you can
// change the colours of your display boxes according to the 
// sensor readings
AndeeHelper colourDisplay;

// We'll use Analog Input Pin A0 to read in the analog input
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
  // Let's draw discreteDisplay first!
  colourDisplay.setId(0);  // Each object must have a unique ID number
  colourDisplay.setType(DATA_OUT);  // This defines your object as a display box
  colourDisplay.setLocation(0, 0, FULL); // Sets the location and size of your object
  colourDisplay.setTitle("Colour Change"); // Sets title
  colourDisplay.setData(""); // We'll update it with new analog data later.
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // Read values from analog pins and store it in int variables
  int reading = analogRead(analogInputPin); 
  
  if(reading < 300) // Feel free to change the value
  {
    colourDisplay.setColor(GREEN); // Sets background colour
    
    /* Or you can use the ARGB colour code to set your own colour, in the form:
    colourDisplay.setColor("FF00FF00"); */
    
    colourDisplay.setTextColor(BLACK); // Sets font colour. 
    
    colourDisplay.setTitleColor(GREEN); // Sets title background colour
    colourDisplay.setTitleTextColor(BLACK); // Sets title font colour
  }
  else if(reading < 350) // Feel free to change the value
  {
    colourDisplay.setColor(YELLOW);
    colourDisplay.setTextColor(BLACK);
    colourDisplay.setTitleColor(YELLOW);
    colourDisplay.setTitleTextColor(BLACK);
  }
  else
  { 
    colourDisplay.setColor(RED);
    colourDisplay.setTextColor(WHITE);
    colourDisplay.setTitleColor(RED);
    colourDisplay.setTitleTextColor(WHITE);
  }
  
  colourDisplay.setData(reading); // Set the display box with new data value
  colourDisplay.update(); // Update the display to show the new value
  
  // A short delay is necessary to give Andee time to communicate with the smartphone
  delay(500); 
}

// FUN FACT! Did you know that if you press and hold your finger on the display box, your phone will
// draw a graph? Also, setColor() sets the colour of your graph line!


