/************************************************************
  [Annikken Andee]
  ================
  Lesson 14
  Retrieving Text Input from Smartphone
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

// We'll create a text input button and a display box to display
// the user input
AndeeHelper displaybox;
AndeeHelper textInputButton;
char userInput[32];

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
  displaybox.setTitle("Here's what you wrote");
  
  textInputButton.setId(1);
  textInputButton.setType(KEYBOARD_IN); // Sets object as a text input button
  textInputButton.setLocation(1,0,FULL);
  textInputButton.setTitle("Type something!");
  textInputButton.setKeyboardType(ALPHA_NUMERIC); 
  /* Sets the type of keyboard to show to the user
  Options available are:
    - ALPHA_NUMERIC - Alpha-numeric keyboard.
    - ALPHA_NUMERIC_PW - Alpha-numeric keyboard, input as password.
    - ANDROID_NUMERIC - Android OS numeric keyboard.
    - ANDROID_NUMERIC_PW - Android OS numeric keyboard, input as password.
    - ANDEE_NUMERIC_A - Andee's Numeric Keyboard. Integer values only.
    - ANDEE_NUMERIC_A_PW - Andee's Numeric Keyboard. Integer values only. Input as password.
    - ANDEE_NUMERIC_B - Andee's Numeric Keyboard. For float/double values.
    - ANDEE_NUMERIC_B_PW - Andee's Numeric Keyboard. For float/double values. Input as password. 
  */
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( textInputButton.isPressed() )
  {
    memset(userInput, 0x00, 32); // Empty the contents of the string before receiving user input
    textInputButton.ack(); // Acknowledge button press or else phone will be left waiting
    textInputButton.getKeyboardMessage(userInput); // Display keyboard and store input into userInput
    displaybox.setData(userInput); // Display user input on the display box
  }
  
  displaybox.update(); // Always remember to update so that new content will be displayed
  textInputButton.update();
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



