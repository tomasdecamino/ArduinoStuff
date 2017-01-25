/************************************************************
  [Annikken Andee]
  ================
  Lesson 21
  Change Andee Bluetooth Device Name
  by Jonathan Sim <jonathan@annikken.com>

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/

// You only need to run this code once.

#include <Andee.h> // Don't forget the necessary libraries
#include <SPI.h>

// This is where you change your device name:
char newBluetoothName[] = "Hello New Device Name"; // New device name
char cmdReply[64]; // String buffer
char commandString[100]; // String to store the new device name and device command into one

void setup()
{
  Andee.begin();
  Andee.clear();

  // We need to combine the new device name with the device command
  sprintf(commandString, "SET BT NAME %s", newBluetoothName);
  // Send command to change device name
  Andee.sendCommand(commandString, cmdReply);
}

void loop()
{
  // Disconnect user - there's nothing to do here anyway
  if(Andee.isConnected()) 
    Andee.disconnect();
}
