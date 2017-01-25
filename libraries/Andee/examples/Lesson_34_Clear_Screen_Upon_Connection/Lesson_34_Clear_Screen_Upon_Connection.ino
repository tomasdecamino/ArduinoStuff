/************************************************************
  [Annikken Andee]
  ================
  Lesson 34
  Clearing Device Screen Upon Connection
  by Teo Boon Keat <bkteo@annikken.com>
  
  A connection may be made when your sketch is running in the
  loop function. It may then be desirable to clear the screen
  when a new user connects to your program. This lesson uses
  Andee.isConnected() and some flags to instruct Andee to 
  clear the users screen when he/she first connects.
  
  You should see your screen being cleared after a reconnection.

  Check out our Resources section for more information and 
  ideas on what you can do with the Annikken Andee!
  http://resources.annikken.com
  
  Check out our Blog for regular updates and fun!
  http://annikken.com/blog
************************************************************/
#include <Andee.h>
#include <SPI.h>

AndeeHelper helper;

bool wasConnectedFlag; //boolean flag to keep track of previous connection status
int connection; //return value for Andee.isConnected().

//The Andee.isConnected() function returns CONNECTED, NOT_CONNECTED or TIMEOUT
//TIMEOUT = the function ended prematurely. You should call the function again

void setup(){
  Andee.begin();
  Andee.clear();
  
  helper.setId(0);
  helper.setType(DATA_OUT);
  helper.setLocation(0,0,FULL);
  helper.setTitle("Title");
  helper.setData("Data Field");
 
  wasConnectedFlag = false;
}

void loop(){
  
  connection = Andee.isConnected(); //Get connection status from Andee
  if(connection == CONNECTED && !wasConnectedFlag){
    Andee.clear(); //Clear user's screen of any previous sketches from another Andee
    wasConnectedFlag = true;
  }
  else if(connection == NOT_CONNECTED){
    wasConnectedFlag = false;
  }
  
  helper.update(); //show display on screen
  delay(500);
}
