/*
  SendATweet

  Demonstrates sending a tweet via a Twitter account using the Temboo Arduino Yun SDK.

  This example code is in the public domain.
*/

#include <Bridge.h>
#include <Temboo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define TEMBOO_ACCOUNT "quetzal"  // your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // your Temboo app key name
#define TEMBOO_APP_KEY  "7d1988678da944cdb69c7a45f41f699f"  // your Temboo app key

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.
const String TWITTER_ACCESS_TOKEN = "3048081057-I95bltpTs6s7TM8dJt8TxJxHvEnxlpZjJjOFTWn";
const String TWITTER_ACCESS_TOKEN_SECRET = "r47FFO6OCifq8zAQkmUgSjUGkeRnQgIwSDlZ62rZ1Y21i";
const String TWITTER_API_KEY = "RJBw51yolfDScXxymhOVL6tSs";
const String TWITTER_API_SECRET = "RCdP5Avx8UShf0xwJMCC4wk1ojQaMcBHTWT6338Ip6R6ok4mJS";



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

int numRuns = 1;   // execution count, so this sketch doesn't run forever
int maxRuns = 1;  // the max number of times the Twitter Update Choreo should run
long lastMillis;
int count = 0;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  // for debugging, wait until a serial console is connected
  delay(4000);
  while (!Serial);

  Bridge.begin();
  pinMode(A0, INPUT);
}

void loop()
{
  count = 0;
  lastMillis = millis();
  while (millis() - lastMillis < 240000) {
    if (digitalRead(A0)) {
      moveWings();
      count++;

    }
  }
  Serial.println(count);  
  // only try to send the tweet if we haven't already sent it successfully
  if (numRuns <= maxRuns) {

    Serial.println("Running SendATweet - Run #" + String(numRuns++) + "...");

    // define the text of the tweet we want to send
    String tweetText("He abierto mis alas " + String(count) + " veces");


    TembooChoreo StatusesUpdateChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    StatusesUpdateChoreo.begin();

    // set Temboo account credentials
    StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
    StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);

    // identify the Temboo Library choreo to run (Twitter > Tweets > StatusesUpdate)
    StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");

    // set the required choreo inputs
    // see https://www.temboo.com/library/Library/Twitter/Tweets/StatusesUpdate/
    // for complete details about the inputs for this Choreo

    // add the Twitter account information
    StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
    StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
    StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_API_KEY);
    StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_API_SECRET);

    // and the tweet we want to send
    StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);

    // tell the Process to run and wait for the results. The
    // return code (returnCode) will tell us whether the Temboo client
    // was able to send our request to the Temboo servers
    unsigned int returnCode = StatusesUpdateChoreo.run();

    // a return code of zero (0) means everything worked
    if (returnCode == 0) {
      Serial.println("Success! Tweet sent!");
    } else {
      // a non-zero return code means there was an error
      // read and print the error message
      while (StatusesUpdateChoreo.available()) {
        char c = StatusesUpdateChoreo.read();
        Serial.print(c);
      }
    }
    StatusesUpdateChoreo.close();

    // do nothing for the next 90 seconds
  }
}

//degrees to pulses
void moveDegree(int s, int deg) {
  int pulselength = map(deg, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(s, 0, pulselength);
}

void moveWings() {
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
