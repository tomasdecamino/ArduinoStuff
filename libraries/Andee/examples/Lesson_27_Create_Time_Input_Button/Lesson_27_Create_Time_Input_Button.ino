/************************************************************
  [Annikken Andee]
  ================
  Lesson 27
  Create Time Input Button
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

// We'll need a date input button and a display box to provide feedback
AndeeHelper displaybox;
AndeeHelper timeInputButton;

int hh, mm, ss; // Variables to store user time input
char tempString[20]; // Used to store date as a string

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
  displaybox.setId(0);
  displaybox.setType(DATA_OUT);
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Your Selected Time");
  displaybox.setData("No Time Selected");
  
  timeInputButton.setId(1);
  timeInputButton.setType(TIME_IN); // Sets object as a time input button
  timeInputButton.setLocation(1,0,FULL);
  timeInputButton.setTitle("Select Time");
  
  // Optional Setting. When the user opens up the time picker, Andee will display this
  // time as the initial time to choose.
  timeInputButton.setDefaultTime(23, 59, 59); // Format: hour, minute, second
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( timeInputButton.isPressed() )
  { 
    timeInputButton.ack();
    
    // Display time picker and store it in the three variables - hh, mm, and ss
    timeInputButton.getTimeInput(&hh, &mm, &ss); 
    
    // String the three variables into a single time string
    sprintf(tempString, "%02d:%02d:%02d", hh, mm, ss);
    displaybox.setData(tempString);
  }
  
  displaybox.update();
  timeInputButton.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



