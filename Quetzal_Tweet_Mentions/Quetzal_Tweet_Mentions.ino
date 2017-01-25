#include <Bridge.h>
#include <Temboo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define TEMBOO_ACCOUNT "quetzal"  // your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // your Temboo app key name
#define TEMBOO_APP_KEY  "7d1988678da944cdb69c7a45f41f699f"  // your Temboo app key

#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.
const String TWITTER_ACCESS_TOKEN = "3048081057-I95bltpTs6s7TM8dJt8TxJxHvEnxlpZjJjOFTWn";
const String TWITTER_ACCESS_TOKEN_SECRET = "r47FFO6OCifq8zAQkmUgSjUGkeRnQgIwSDlZ62rZ1Y21i";
const String TWITTER_API_KEY = "RJBw51yolfDScXxymhOVL6tSs";
const String TWITTER_API_SECRET = "RCdP5Avx8UShf0xwJMCC4wk1ojQaMcBHTWT6338Ip6R6ok4mJS";

int numRuns = 1;   // execution count, so this doesn't run forever
int maxRuns = 20;   // the max number of times the Twitter HomeTimeline Choreo should run
uint8_t servonum = 0;

String author;
String lastAuthor = "";
long lastMillis;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // For debugging, wait until a serial console is connected.
  delay(4000);
  while (!Serial);
  Bridge.begin();
}
void loop()
{
  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {
    Serial.println("Running ReadATweet - Run #" + String(numRuns++));

    /**********read mentions timeline******************/
    TembooChoreo  LatestMentionChoreo;
    // invoke the Temboo client.
    // NOTE that the client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    LatestMentionChoreo.begin();

    // set Temboo account credentials
    LatestMentionChoreo.setAccountName(TEMBOO_ACCOUNT);
    LatestMentionChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    LatestMentionChoreo.setAppKey(TEMBOO_APP_KEY);

    // tell the Temboo client which Choreo to run (Twitter > Timelines > HomeTimeline)
    LatestMentionChoreo.setChoreo("/Library/Twitter/Timelines/LatestMention");


    // set the required choreo inputs
    // see https://www.temboo.com/library/Library/Twitter/Timelines/HomeTimeline/
    // for complete details about the inputs for this Choreo

    LatestMentionChoreo.addInput("Count", "1"); // the max number of Tweets to return from each request
    LatestMentionChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
    LatestMentionChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
    LatestMentionChoreo.addInput("ConsumerKey", TWITTER_API_KEY);
    LatestMentionChoreo.addInput("ConsumerSecret", TWITTER_API_SECRET);

    // next, we'll define two output filters that let us specify the
    // elements of the response from Twitter that we want to receive.
    // see the examples at http://www.temboo.com/arduino
    // for more on using output filters

    // we want the text of the tweet
    LatestMentionChoreo.addOutputFilter("tweet", "/[1]/text", "Response");

    // and the name of the author
    LatestMentionChoreo.addOutputFilter("author", "/[1]/user/screen_name", "Response");

    unsigned int returnCode = LatestMentionChoreo.run();

    // a response code of 0 means success; print the API response
    if (returnCode == 0) {

      // String author; // a String to hold the tweet author's name
      String tweet; // a String to hold the text of the tweet

      while (LatestMentionChoreo.available()) {
        // read the name of the output item
        String name = LatestMentionChoreo.readStringUntil('\x1F');
        name.trim();

        // read the value of the output item
        String data = LatestMentionChoreo.readStringUntil('\x1E');
        data.trim();

        // assign the value to the appropriate String
        if (name == "tweet") {
          tweet = data;
        } else if (name == "author") {
          lastAuthor = author;
          author = data;
        }

      }

      Serial.println("@" + author + " - " + tweet);

      /****** write tweet *******/






    } else {
      // there was an error
      // print the raw output from the choreo
      while (LatestMentionChoreo.available()) {
        char c = LatestMentionChoreo.read();
        Serial.print(c);
      }
    }

    LatestMentionChoreo.close();

  }

  /* servo movent */
  if (lastAuthor != author) {
    moveWings();



  }else{
     Serial.println("not moving..."); 
  }

  lastMillis=millis();
  while(millis()-lastMillis<120000){
    
  }
}

void moveDegree(int s, int deg) {
  int pulselength = map(deg, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(s, 0, pulselength);
}

void moveWings(){
     for (uint16_t deg = 0; deg < 180; deg++) {
      moveDegree(0, 180 - deg);
      moveDegree(1, deg / 2);
      moveDegree(2, deg);
      moveDegree(3, 90 - deg / 2);
      delay(5 + sq(deg - 90) / 90);
      //Serial.println(deg);
    }
    delay(10000);
    for (uint16_t deg = 180; deg > 0; deg--) {
      moveDegree(0, 180 - deg);
      moveDegree(1, deg / 2);
      moveDegree(2, deg);
      moveDegree(3, 90 - deg / 2);
      delay(5 + sq((180 - deg) - 90) / 90);
    }
    delay(1000);

 
  
}
