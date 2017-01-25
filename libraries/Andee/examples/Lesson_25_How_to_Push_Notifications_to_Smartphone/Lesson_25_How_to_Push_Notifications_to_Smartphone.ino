/************************************************************
  [Annikken Andee]
  ================
  Lesson 25
  How to Push Notifications to Smartphone
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

// We'll use a button to send the message
AndeeHelper btnNotify;
AndeeHelper notificationObject; // The notification must be declared as an object

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
  btnNotify.setId(0);
  btnNotify.setType(BUTTON_IN);
  btnNotify.setLocation(0,0,FULL);
  btnNotify.setTitle("Push Notification");
  
  notificationObject.setId(1);
  notificationObject.setType(NOTIFICATION); // Sets object as an SMS object
  notificationObject.setTitle("Notification Title"); 
  notificationObject.setMessage("Notification Message"); 
  notificationObject.setTicker("Text that appears at status bar when notification is pushed"); 
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( btnNotify.isPressed() ) // When user presses the send button on phone
  {
    btnNotify.ack(); // Acknowledge button press
    notificationObject.notify(); // Sends the SMS to the recipient
  }

  btnNotify.update();
  // Do not update SMS objects!
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



