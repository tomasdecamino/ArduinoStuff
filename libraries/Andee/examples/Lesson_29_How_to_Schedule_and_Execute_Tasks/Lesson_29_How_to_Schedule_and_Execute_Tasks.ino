/************************************************************
  [Annikken Andee]
  ================
  Lesson 29
  How to Schedule and Execute Tasks
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

/* We'll just turn on an LED to demonstrate this function. You can do 
   other things with this, like an alarm clock or automatic data logger. */

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <SPI.h>
#include <Andee.h>

// There are two ways to retrieve the date and time from your smartphone
// We'll create two objects to demonstrate these two ways.
AndeeHelper displaybox;
// Current Date/Time
int day;
int month;
int year;
int hour; 
int minute;
int second;
// Scheduled Date/Time. You can use the date/time input buttons
// to allow the user schedule the tasks
int scheduledDay = 31; // Go ahead and change the date/time to see this at work!
int scheduledMonth = 12;
int scheduledYear = 2013;
int scheduledHour = 23;
int scheduledMinute = 59;
int scheduledSecond = 0;
// Flag variable to indicate whether the scheduled command was executed
int executedFlag = 0; 

const int outputPin = 2; // LED connected to Pin 2

char tempString[30];

// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  
  pinMode(outputPin, OUTPUT);
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  displaybox.setId(0);
  displaybox.setType(DATA_OUT);
  displaybox.setLocation(0,0,FULL);
  displaybox.setTitle("Current Date/Time");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( Andee.isConnected() )
  {
    // Retrieve date and store in variables: day, month, and year
    Andee.getDeviceDate(&day, &month, &year);
    // Retrieve time and store in variables: hour, minute, second
    Andee.getDeviceTime(&hour, &minute, &second);
    sprintf(tempString, "%d/%d/%d, %02d:%02d:%02d", day, month, year, hour, minute, second);
    
    // Execute at the scheduled date/time
    if(day == scheduledDay
     && month == scheduledMonth
     && year == scheduledYear
     && hour == scheduledHour
     && minute == scheduledMinute
     && second >= scheduledSecond // We're using >= instead just to prevent the occasion that Arduino hangs for a while and misses that crucial second
     && executedFlag == 0)
    {
       digitalWrite(outputPin, HIGH);
       displaybox.setTitle("Scheduled Task Executed");
       executedFlag = 1; // To stop it from repeating again
    } 
    
    displaybox.setData(tempString);
    displaybox.update();
  }
  
  delay(500); // Always leave a short delay for Bluetooth communication
}
