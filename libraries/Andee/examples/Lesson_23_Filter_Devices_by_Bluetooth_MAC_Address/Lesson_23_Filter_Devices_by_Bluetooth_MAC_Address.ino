/************************************************************
  [Annikken Andee]
  ================
  Lesson 23
  Filter Devices by Bluetooth MAC Address
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

// We'll need a display box to display the connected MAC address
AndeeHelper displaybox;

// This list will contain all the authorised MAC addresses
char *authorisedList[] = { "00:11:22:33:44:55",
                         "aa:bb:cc:dd:ee:ff", 
                         "aa:11:bb:22:cc:33" };  // Don't forget to add yours!
int noOfAuthorisedUsers = 3;

char strBuffer[30]; // String to store the retrieved Bluetooth info
char current_mac_id[18]; // String to store the extracted MAC address
bool authorised; // Flag to check if user is authorised or not


// The setup() function is meant to tell Arduino what to do 
// only when it starts up.
void setup()
{
  Andee.begin();  // Setup communication between Annikken Andee and Arduino
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData(); // Define object types and their appearance
  authorised = false;
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
  if( Andee.isConnected() ) // When user presses the send button on phone
  {
     // Send command to the Andee to get some Bluetooth device information
     // and store it in the string buffer
     Andee.sendCommand("GET CONNECTED MAC_ID", strBuffer);
    
     // As the retrieved information contains more than just the MAC address,
     // we'll need to extract the MAC address and store it in another string
     strncpy(current_mac_id, strBuffer, 17); // Extract MAC address
     
     for(int i = 0; i < noOfAuthorisedUsers; i++)
     {
       if( strcmp(current_mac_id, authorisedList[i]) == 0 )
       {
         authorised = true; // Mark flag as true if connected device is in authorised list
       }
     }
     
     if(authorised == true) // If user is authorised
     {
       // This is where you'll show the authorised user the controls that you want to show
       displaybox.setData("You are authorised!"); 
       displaybox.update();    
     }
     else // If intruder
     {
       // Show a message before you disconnect the intruder
       displaybox.setData("Intruder! You will be disconnected!"); 
       displaybox.update();             
       delay(2000); // Give intruder time to read the message
       Andee.disconnect(); // Disconnect intruder
     }

  }
  else // If not connected
  {
    authorised = false; // Reset flag to false when authorised users disconnect
  }
  
  delay(500); // Always leave a short delay for Bluetooth communication
}



