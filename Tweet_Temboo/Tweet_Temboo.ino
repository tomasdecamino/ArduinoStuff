/*
  SendDirectMessage

  Demonstrates sending a Twitter Direct Message using the Temboo Arduino Yun SDK.
  
  This example code is in the public domain.
*/

#include <Bridge.h>
#include <Temboo.h>

#define TEMBOO_ACCOUNT "quetzal"  // your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // your Temboo app key name
#define TEMBOO_APP_KEY  "7d1988678da944cdb69c7a45f41f699f"  // your Temboo app key

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.
const String TWITTER_ACCESS_TOKEN = "3048081057-I95bltpTs6s7TM8dJt8TxJxHvEnxlpZjJjOFTWn";
const String TWITTER_ACCESS_TOKEN_SECRET = "r47FFO6OCifq8zAQkmUgSjUGkeRnQgIwSDlZ62rZ1Y21i";
const String TWITTER_API_KEY = "MBgLq3v7ftiJduOnUGhQnMSKV";
const String TWITTER_API_SECRET = "MqFeLphBQX1hlYs2ifWWktenNngSt6ez48Q8wmVYD60reC12yy";

// your twitter screen name will be something like @temboo or @cormacdriver
const String TWITTER_NAME ="your-twitter-account-name";

int numRuns = 1;   // execution count, so this sketch doesn't run forever
int maxRuns = 1;  // the max number of times the Twitter Direct Message Choreo should run

void setup() {
  Serial.begin(9600);

  // for debugging, wait until a serial console is connected
  delay(4000);
  while(!Serial);

  Bridge.begin();
}

void loop()
{
  // only try to send the direct message if we haven't already sent it successfully
  if (numRuns <= maxRuns) {

    Serial.println("Running SendDirectMessage - Run #" + String(numRuns++) + "...");
  
    // define the text of the direct message we want to send
    String tweetText("My Arduino Yun has been running for " + String(millis()) + " milliseconds.");
    
    TembooChoreo SendDirectMessageChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    SendDirectMessageChoreo.begin();
    
    // set Temboo account credentials
    SendDirectMessageChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendDirectMessageChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendDirectMessageChoreo.setAppKey(TEMBOO_APP_KEY);

    // identify the Temboo Library choreo to run (Twitter > DirectMessages > SendDirectMessage)
    SendDirectMessageChoreo.setChoreo("/Library/Twitter/DirectMessages/SendDirectMessage");

    // set the required choreo inputs
    // see https://www.temboo.com/library/Library/Twitter/DirectMessages/SendDirectMessage 
    // for complete details about the inputs for this Choreo
 
    // add the Twitter account information
    SendDirectMessageChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
    SendDirectMessageChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
    SendDirectMessageChoreo.addInput("ConsumerKey", TWITTER_API_KEY);    
    SendDirectMessageChoreo.addInput("ConsumerSecret", TWITTER_API_SECRET);

    // and the direct messae we want to send
    SendDirectMessageChoreo.addInput("Text", tweetText);
    
    // and the user who we want to send the DM to
    SendDirectMessageChoreo.addInput("ScreenName", TWITTER_NAME);
    
    
    // tell the process to run and wait for the results. The 
    // return code (returnCode) will tell us whether the Temboo client 
    // was able to send our request to Temboo 
    unsigned int returnCode = SendDirectMessageChoreo.run();

    // a return code of zero (0) means everything worked
    if (returnCode == 0) {
        Serial.println("Success! Direct message sent!");
    } else {
      // a non-zero return code means there was an error
      // read and print the error message
      while (SendDirectMessageChoreo.available()) {
        char c = SendDirectMessageChoreo.read();
        Serial.print(c);
      }
    } 
    SendDirectMessageChoreo.close();

    // do nothing for the next 90 seconds
    Serial.println("Done.");
    delay(90000);
  }
}
