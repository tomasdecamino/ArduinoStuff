/************************************************************
  [Annikken Andee]
  ================
  Lesson 24
  How to Send SMS
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
AndeeHelper sendMessage;
AndeeHelper SMSobject; // The message and recipient must be declared as an object

// You can use the text input button to get the user to set the
// recipient number and even the message itself!
char messageRecipient[] = "+6587654321";
char message[] = "Hello World!";

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
  sendMessage.setId(0);
  sendMessage.setType(BUTTON_IN);
  sendMessage.setLocation(0,0,FULL);
  sendMessage.setTitle("Send SMS");
  
  SMSobject.setId(1);
  SMSobject.setType(SMS_SENDER); // Sets object as an SMS object
  SMSobject.setRecipient(messageRecipient);
  SMSobject.setMessage(message);
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( sendMessage.isPressed() ) // When user presses the send button on phone
  {
    sendMessage.ack(); // Acknowledge button press
    SMSobject.send(); // Sends the SMS to the recipient
  }

  sendMessage.update();
  // Do not update SMS objects!
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



