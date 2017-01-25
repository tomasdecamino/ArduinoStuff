/************************************************************
  [Annikken Andee]
  ================
  Lesson 31
  How to Get Your Smartphone to Talk
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// If you do not hear anything from your phone, you will need to 
// disable silent mode or check your phone's system volume settings.
// If that does not work, you may need to manually configure
// Text to Speech. To do this, go to the Andee app, and open
// "Settings." Scroll down and you should find a "Setup" button
// under the TTS section.

// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <Andee.h>
#include <SPI.h>

AndeeHelper displaybox;
AndeeHelper button;
AndeeHelper speechObject; // You need to create a speech object for the phone to talk

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
  displaybox.setTitle("Text to Speech");
  displaybox.setData("Be sure to unmute your phone to hear your phone talk!");  
  
  button.setId(1); // Don't forget to assign a unique ID number
  button.setType(BUTTON_IN); // Defines object as a button
  button.setLocation(1,0,FULL);
  button.setTitle("Say something!");
  button.setColor(THEME_RED_DARK);
  
  speechObject.setId(2);
  speechObject.setType(TTS); // Defines object as a Text-to-Speech object
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( button.isPressed() )
  {
    button.ack();
    // Use updateData() to get the phone to talk!
    speechObject.updateData("Confucius say: Man run in front of car get tired,"); 
    speechObject.updateData("man run behind car get exhausted."); 
    // You will need to break your sentence into multiple lines if your lines are too long.
    // Each speech object can only handle up to 40 characters of text at a time.
    // Punctuation will also affect the way your phone vocalises the text.
  }
  
  displaybox.update();
  button.update();
  // Do not update the speechObject!
  
  delay(500); // Always leave a short delay for Bluetooth communication
}




