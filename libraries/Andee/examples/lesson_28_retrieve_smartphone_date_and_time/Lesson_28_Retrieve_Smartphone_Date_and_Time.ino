/************************************************************
  [Annikken Andee]
  ================
  Lesson 28
  Retrieve Smartphone Date and Time
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

// There are two ways to retrieve the date and time from your smartphone
// We'll create two objects to demonstrate these two ways.
AndeeHelper methodOne;
AndeeHelper methodTwo;

char methodOneString[30];
char methodTwoString[30]; 
int day;
int month;
int year;
int hour; 
int minute;
int second;

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
  methodOne.setId(0);
  methodOne.setType(DATA_OUT);
  methodOne.setLocation(0,0,FULL);
  methodOne.setTitle("Method One");
  
  methodTwo.setId(1);
  methodTwo.setType(DATA_OUT);
  methodTwo.setLocation(1,0,FULL);
  methodTwo.setTitle("Method Two");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  /////// Method One /////////
  // Useful only if you want to display the date/time and nothing more.
  // Refer to http://resources.annikken.com/index.php?title=How_to_retrieve_the_smartphone%27s_date/time_as_a_string
  // for formatting options
  Andee.printDeviceTime("%A, %d %B %Y, %I:%M:%S %p", methodOneString);
  methodOne.setData(methodOneString);
  methodOne.update();
  
  /////// Method Two /////////
  // Useful if you need to check the current time to execute a scheduled task
  // Retrieve date and store in variables: day, month, and year
  Andee.getDeviceDate(&day, &month, &year);
  // Retrieve time and store in variables: hour, minute, second
  Andee.getDeviceTime(&hour, &minute, &second);
  sprintf(methodTwoString, "%d/%d/%d, %02d:%02d:%02d", day, month, year, hour, minute, second);
  methodTwo.setData(methodTwoString);
  methodTwo.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



