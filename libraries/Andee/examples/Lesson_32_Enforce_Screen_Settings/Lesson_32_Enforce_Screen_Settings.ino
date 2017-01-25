/************************************************************
  [Annikken Andee]
  ================
  Lesson 32
  Enforce Screen Settings
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// This lesson will teach you two things:
// - How to make sure the screen stays always on
// - How to enforce screen orientation

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <Andee.h>
#include <SPI.h>

// We'll just create a display box
AndeeHelper displaybox;

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  // If you want your screen to remain on at all times, call this function:
  Andee.screenAlwaysOn(true);
  // This will prevent your phone from sleeping.
  // You can call Andee.screenAlwaysOn() anytime in your code.
  // To allow your phone to go back to sleep, call: Andee.screenAlwaysOn(false);
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  // Let's draw the button!
  displaybox.setId(0); // Don't forget to assign a unique ID number
  displaybox.setType(DATA_OUT); // Defines object as a display box
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Current Orientation Mode");
  displaybox.setUnit("Screen orientation will change every 5 seconds");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // This loop will demonstrate the various screen orientation modes
  // that you can enforce.
  // You can call these commands within the setup() function. I have
  // placed them here just to demonstrate the various screen
  // orientation modes that you can enforce.
  for(int i = 0; i < 5; i++)
  {
    if(i == 0)
    {
      // Enforce auto-orientation
      Andee.setScreenOrientation(AUTO);
      displaybox.setData("AUTO");
    }
    if(i == 1)
    {
      // Enforce portrait orientation
      Andee.setScreenOrientation(PORTRAIT);
      displaybox.setData("PORTRAIT");
    }
    if(i == 2)
    {
      // Enforce landscape orientation
      Andee.setScreenOrientation(LANDSCAPE);
      displaybox.setData("LANDSCAPE");
    }
    if(i == 3)
    {
      // Enforce upside down portrait orientation
      Andee.setScreenOrientation(PORTRAIT_REVERSE);
      displaybox.setData("PORTRAIT_REVERSE");
    }
    if(i == 4)
    {
      // Enforce upside down landscape orientation
      Andee.setScreenOrientation(LANDSCAPE_REVERSE);
      displaybox.setData("LANDSCAPE_REVERSE");
    }
    displaybox.update();
    delay(5000); // Always leave a short delay for Bluetooth communication
  }
}




