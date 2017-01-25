/************************************************************
  [Annikken Andee]
  ================
  Lesson 22
  How to Filter Bluetooth Connections
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

// We'll use a display box to show the current MAC address
AndeeHelper displaybox;

char strBuffer[30]; // String to store the retrieved Bluetooth info
char current_mac_id[18]; // String to store the extracted MAC address

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
  displaybox.setTitle("Connected MAC Address");
}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  if( Andee.isConnected() ) // Do this only when Andee is connected
  {
    // Send command to the Andee to get some Bluetooth device information
    // and store it in the string buffer
    Andee.sendCommand("GET CONNECTED MAC_ID", strBuffer);
    
    // As the retrieved information contains more than just the MAC address,
    // we'll need to extract the MAC address and store it in another string
    strncpy(current_mac_id, strBuffer, 17); // Extract MAC address
    
    displaybox.setData(current_mac_id);
    displaybox.update();
  }
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



