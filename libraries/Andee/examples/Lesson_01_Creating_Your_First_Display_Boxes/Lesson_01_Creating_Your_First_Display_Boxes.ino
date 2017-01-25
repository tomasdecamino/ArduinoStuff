/************************************************************
  [Annikken Andee]
  ================
  Lesson 1
  Creating Your First Display Boxes!
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

// Every object that appears on your smartphone's screen
// needs to be declared like this:
AndeeHelper objectA;
AndeeHelper objectB;
// We're creating two objects

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
  //// Let's draw the first object! //////////////////////////////////////////

  objectA.setId(0);  // Each object must have a unique ID number
  objectA.setType(DATA_OUT);  // This defines your object as a display box
  objectA.setLocation(0, 0, FULL); // Sets the location and size of your object
  /* setLocation (row, col, size)
     Row: From 0 (top-most) to 3
     Col: From 0 (left-most) to 9. If there are too many objects on that row, you can
          scroll from left to right.
     Size: The following sizes are available for you to chooose:
     FULL, HALF, ONE_THIRD, ONE_QUART, TWO_THIRD, THREE_QUART */
  objectA.setTitle("This goes to the title bar");
  objectA.setData("This goes to the data field");
  objectA.setUnit("This goes to the units field"); // Optional
    
  
  //// Let's draw the second object! ////////////////////////////////////////
  
  objectB.setId(1); // Don't forget to give it a unique ID number
  objectB.setType(DATA_OUT); // Another display box
  objectB.setLocation(1,0,FULL); // Second row, left-most, full size
  objectB.setTitle("Hello");
  objectB.setData("World!");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  objectA.update(); // Call update() to refresh the display on your screen
  objectB.update(); // If you forgot to call update(), your object won't appear
  
  // A short delay is necessary to give Andee time to communicate with the smartphone
  delay(500); 
}



