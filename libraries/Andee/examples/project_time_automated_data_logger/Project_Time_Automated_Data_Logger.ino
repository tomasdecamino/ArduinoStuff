/************************************************************
  [Annikken Andee]
  ================
  Time Automated Data Logger
  by Jonathan Sim <jonathan@annikken.com>

  This sample project allows the user to schedule the start
  and end date/time, and the frequency of a data logging task.
  As a sample project, it makes use of the TMP36 temperature
  sensor to take a reading and logs the data in a CSV file.
  You can then make use of the CSV file to plot a graph!
  
  This project requires an SD Card.
 
  For video instructions on how to assemble this, 
  please visit http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

#include <SPI.h> 
#include <Andee.h>
#include <String.h>

AndeeHelper displayCurrentInfo; // Display current date/time and temperature reading
AndeeHelper btnStartTime; // Button to schedule start time of logging
AndeeHelper btnStartDate; // Button to schedule start date of logging
AndeeHelper btnEndTime; // Button to schedule end time of logging
AndeeHelper btnEndDate; // Button to schedule end date of logging
AndeeHelper btnSetLogFreq; // Button to set logging frequency (in seconds)
AndeeHelper displayLogStatus; // Display logging status
const int pinTempSensor = A0; // Our temp sensor is connected to pin A0

// String buffers to store the contents of sprintf() before displaying them
char outputString[50];
char tempStr[50];

// Flags
int clockOK = 0; // Flag to check whether a set of instructions have been run once
int flagLogging = 0; // Flag to indicate whether logging has started or not

// Date/time variables for start, end, and current. Start and end variables
// are initialised as 99 to indicate that the time/date hasn't been configured
int s_hh = 99, s_mm = 99, s_ss = 99, s_d = 99, s_m = 99, s_y = 99;
int e_hh = 99, e_mm = 99, e_ss = 99, e_d = 99, e_m = 99, e_y = 99;
int hh, mm, ss, d, m, y;
int freq = 0; // Frequency in seconds
int logcount = 0; // Counter
long timenow; // Store timestamp
long timeold; // Store old timestamp to check if time is due for the next log

// Variables necessary for SD card read/write
char filename[] = "log.csv";
int offset=0;
char errorMsgBuffer[64];

void setup()
{
  Andee.begin(); // Sets up the communication link between Arduino and the Annikken Andee
  Andee.clear(); // Clear the screen of any previous displays
  setInitialData(); // Define objects to be drawn on the screen
  
  analogReference(EXTERNAL); // External analog reference in use for temp sensor
  
  // Write table headers to SD card
  sprintf(outputString, "Time, Temperature\n");
  offset = Andee.writeSD(filename, outputString, offset, errorMsgBuffer);
  
  // Show error message on screen if there's a problem, e.g. no SD card found
  if(offset == -1) displayLogStatus.updateData(errorMsgBuffer);
  
  delay(1000);
}

void setInitialData()
{  
  displayCurrentInfo.setId(0);
  displayCurrentInfo.setType(DATA_OUT);
  displayCurrentInfo.setLocation(0,0,FULL);
  displayCurrentInfo.setTitle("Arduino x Andee DataLogger");
  displayCurrentInfo.setData("");
  
  btnStartTime.setId(1);
  btnStartTime.setType(TIME_IN);
  btnStartTime.setLocation(1,0,ONE_QUART);
  btnStartTime.setTitle("Set Start Time");
  
  btnStartDate.setId(2);
  btnStartDate.setType(DATE_IN);
  btnStartDate.setLocation(1,1,ONE_QUART);
  btnStartDate.setTitle("Set Start Date");
  
  btnEndTime.setId(3);
  btnEndTime.setType(TIME_IN);
  btnEndTime.setLocation(1,2,ONE_QUART);
  btnEndTime.setTitle("Set End Time");
  
  btnEndDate.setId(4);
  btnEndDate.setType(DATE_IN);
  btnEndDate.setLocation(1,3,ONE_QUART);
  btnEndDate.setTitle("Set End Date");
  
  btnSetLogFreq.setId(5);
  btnSetLogFreq.setType(KEYBOARD_IN);
  btnSetLogFreq.setKeyboardType(ANDROID_NUMERIC);
  btnSetLogFreq.setLocation(2,0,FULL);
  btnSetLogFreq.setTitle("Set Logging Frequency (in seconds)");
  
  displayLogStatus.setId(6);
  displayLogStatus.setType(DATA_OUT);
  displayLogStatus.setLocation(3,0,FULL);
  displayLogStatus.setTitle("Logging Status");
  displayLogStatus.setData("Waiting to Start");
} 

double getTemp()
{
  // Reads analog sensor reading, and translates sensor reading to
  // temperature in degrees Celsius
  return ((analogRead(pinTempSensor) * 3.3 / 1024.0) - 0.5) * 100.0;
}

void loop()
{
  // Button Actions
  if(btnStartTime.isPressed())
  {
    // Get time input and store hour, min, seconds into these three variables
    btnStartTime.getTimeInput(&s_hh, &s_mm, &s_ss);
    btnStartTime.ack();

    // Once user has input time, change button to a display and show the start time
    sprintf(tempStr, "%02d:%02d:%02d", s_hh, s_mm, s_ss);
    btnStartTime.setType(DATA_OUT);
    btnStartTime.setTitle("Start Time");
    btnStartTime.setData(tempStr);
    btnStartTime.update();
  }
  if(btnEndTime.isPressed())
  {
    // Get time input and store hour, min, seconds into these three variables
    btnEndTime.getTimeInput(&e_hh, &e_mm, &e_ss);
    btnEndTime.ack();

    // Once user has input time, change button to display and show the end time
    sprintf(tempStr, "%02d:%02d:%02d", e_hh, e_mm, e_ss);
    btnEndTime.setType(DATA_OUT);
    btnEndTime.setTitle("End Time");
    btnEndTime.setData(tempStr); 
    btnEndTime.update();
  }
  if(btnStartDate.isPressed())
  {    
    // Get date input and store day, month, year into these three variables
    btnStartDate.getDateInput(&s_d, &s_m, &s_y);
    btnStartDate.ack();
 
    // Change button to display and show start date   
    sprintf(tempStr, "%02d/%02d/%4d", s_d, s_m, s_y);    
    btnStartDate.setType(DATA_OUT);
    btnStartDate.setTitle("Start Date");
    btnStartDate.setData(tempStr); 
    btnStartDate.update(); 
  }
  if(btnEndDate.isPressed())
  {    
    // Get date input and store day, month, year into these three variables
    btnEndDate.getDateInput(&e_d, &e_m, &e_y);
    btnEndDate.ack();

    // Change button to display and show end date
    sprintf(tempStr, "%02d/%02d/%4d", e_d, e_m, e_y); 
    btnEndDate.setType(DATA_OUT);
    btnEndDate.setTitle("End Date");
    btnEndDate.setData(tempStr);   
    btnEndDate.update(); 
  }
  if(btnSetLogFreq.isPressed())
  {
    // Get user input for logging frequency (in seconds)
    btnSetLogFreq.getKeyboardMessage(tempStr);
    btnSetLogFreq.ack();
    
    freq = atoi(tempStr); // Convert from string to int

    // Change button to display, showing frequency
    btnSetLogFreq.setType(DATA_OUT);
    btnSetLogFreq.setTitle("Logging Frequency");
    sprintf(tempStr, "Every %d seconds", freq);
    btnSetLogFreq.update(); 
  }

  // If smartphone is JUST connected to the Andee.
  // Runs this code once at the start of connection  
  if(Andee.isConnected() && clockOK == 0)
  {
    clockOK = 1; // Flags that Andee is connected and we're ready to roll
    
    displayCurrentInfo.update();
    btnStartTime.update();
    btnStartDate.update();
    btnEndTime.update();
    btnEndDate.update();
    btnSetLogFreq.update(); 
    displayLogStatus.update();
    // We're drawing these just once as the buttons don't need to be frequently updated. This is done to conserve system resources.
  }

  // Upon disconnect, reset flag
  if(!Andee.isConnected() && clockOK == 1)
  {
    clockOK = 0;
  }

  // Whenever the Andee is connected, do these things:
  if(Andee.isConnected())
  {
    Andee.getDeviceTime(&hh, &mm, &ss); // Get current time
    Andee.getDeviceDate(&d, &m, &y); // Get current date
    dtostrf(getTemp(), 5, 2, tempStr); // Convert float value to string
    timenow = Andee.getDeviceTimeStamp(); // Get current time stamp
    // Timestamp refers to the system time in seconds. 
    // We're going to calculate the difference in timestamps for greater 
    // accuracy in our logging frequency. Doing this will ensure that our 
    // logs are on time

    // Put all these stuff together into a string    
    sprintf(outputString, "%d-%02d-%02d %02d:%02d:%02d, %s\n", y, m, d, hh, mm, ss, tempStr);

    // If current time/date is now the schedule time/date to start logging    
    if(s_hh == hh && s_mm == mm && s_ss >= ss && s_d == d && s_m == m && s_y == y && flagLogging == 0)
    {
      timeold = timenow; 
      flagLogging = 1; // Activate logging flag
      displayCurrentInfo.setColor(RED);
      displayCurrentInfo.setTitleColor(RED);
      displayCurrentInfo.setTitle("Logging in Progress");
    }     

    // If we just started logging, or difference in timestamp equals logging frequency, write current temperature into SD card      
    if(flagLogging == 1 && (timenow - timeold >= freq || timenow - timeold == 0))
    {
      timeold = timenow;
      sprintf(outputString, "%d-%02d-%02d %02d:%02d:%02d, %s\n", y, m, d, hh, mm, ss, tempStr);
      offset = Andee.writeSD(filename, outputString, offset, errorMsgBuffer);
      if(offset == -1) displayLogStatus.updateData(errorMsgBuffer);
      else
      {
        logcount++; // Increase counter
        sprintf(tempStr, "No. of Entries Logged: %d", logcount);
        displayLogStatus.setData(tempStr);
        displayLogStatus.update();
      }
    }

    // If we are in the midst of logging, and the current time/date is now the scheduled time/date to stop logging    
    if(e_hh == hh && e_mm == mm && e_ss >= ss && e_d == d && e_m == m && e_y == y && flagLogging == 1)
    {
      flagLogging = 0; // Reset flag to stop logging
      displayCurrentInfo.setColor(BLUE);
      displayCurrentInfo.setTitleColor(BLUE);
      displayCurrentInfo.setTitle("Logging Complete!");
    }       
      
    // Print current time
    displayCurrentInfo.setData(outputString);
    displayCurrentInfo.update();
  } 
  delay(500); // Refresh displays every 0.5 second
}
