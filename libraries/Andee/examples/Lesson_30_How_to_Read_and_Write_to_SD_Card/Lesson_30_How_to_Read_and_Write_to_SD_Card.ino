/************************************************************
  [Annikken Andee]
  ================
  Lesson 30
  How to How to Read and Write to SD Card
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
AndeeHelper btnWriteContent;
AndeeHelper displaybox;
AndeeHelper btnResetOffset;
AndeeHelper btnReadContent;

// Essentials for Read/Write to SD Card
char filename[] = "FILENAME.TXT"; // String to store the name of file
char errorMessage[64]; // String to store error message
int offset = 0; // Position of where to read/write data in the file

// Essentials for Writing to SD Card
char dataToWrite[150]; // String to store the data for each line before writing

// Essentials for Reading SD Card
char dataRead[64]; // String to store the data for each line before writing
char delimiter[] = "\n"; // What character to detect as the end of each line
int maxLength = 64; // Maximum length to read from each line
/* You'll need to specify both the maximum length of characters per 
   line and the delimiter. readLineFromSD() will read stop reading in 
   a line when it reaches the maximum length OR the delimiter, depending
   on which it encounters first. */

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
  btnWriteContent.setId(0);
  btnWriteContent.setType(KEYBOARD_IN); // Defines object as a text input button
  btnWriteContent.setKeyboardType(ALPHA_NUMERIC); // Defines the keyboard type to use
  btnWriteContent.setLocation(0,0,FULL); // First row, left-most, full width
  btnWriteContent.setTitle("Write to SD Card");
  btnWriteContent.setColor(THEME_DEFAULT_DARK);
  
  displaybox.setId(1);
  displaybox.setType(DATA_OUT);
  displaybox.setLocation(1,0,FULL);
  displaybox.setTitle("Read/Write SD Card Status");

  btnResetOffset.setId(2);
  btnResetOffset.setType(BUTTON_IN);
  btnResetOffset.setLocation(2,0,FULL);
  btnResetOffset.setTitle("Return to Start of File");
  btnResetOffset.setColor(THEME_DEFAULT_DARK);
  
  btnReadContent.setId(3);
  btnReadContent.setType(BUTTON_IN);
  btnReadContent.setLocation(3,0,FULL);
  btnReadContent.setTitle("Read Next Line");
  btnReadContent.setColor(THEME_DEFAULT_DARK);
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  // This is how you write data to an SD Card
  if( btnWriteContent.isPressed() )
  {
   // Show on-screen keyboard to get user input and store in "dataToWrite" 
   btnWriteContent.getKeyboardMessage(dataToWrite);
  
   // Write data to SD card
   offset = Andee.writeSD(filename, dataToWrite, offset, errorMessage);
   offset = Andee.writeSD(filename, "\n", offset, errorMessage); // Insert a next line character
  
   // If there is an error
   if(offset == -1)
   {
     // Show error message on another display box
     displaybox.setData(errorMessage); 
     displaybox.update();
   }
   else
   {
     displaybox.setData("Data Successfully Written!"); 
     displaybox.update();
   }
  
   // Tell smartphone that button press message has been received
   btnWriteContent.ack(); 
  }
  
  // This is how you read data
  if( btnReadContent.isPressed() )
  {
   // Read data from SD card and store it in a string
   offset = Andee.readLineFromSD(filename, offset, dataRead, maxLength, delimiter);
  
   // Display the data from SD card onto a display box
   displaybox.setData(dataRead);
   displaybox.update();
  
   // Tell smartphone that button press message has been received
   btnReadContent.ack(); 
  }  
  
  if( btnResetOffset.isPressed() )
  {
    btnResetOffset.ack();
    offset = 0;
    displaybox.setData("Offset Reset to Zero");
    displaybox.update();
  }
  
  displaybox.update();
  btnResetOffset.update();
  btnWriteContent.update();
  btnReadContent.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}
