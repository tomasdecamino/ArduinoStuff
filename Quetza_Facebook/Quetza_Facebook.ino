/*
  UpdateFacebookStatus

  Demonstrates sending a Facebook status update using the Temboo Arduino Yun SDK.

  This example code is in the public domain.
*/

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
// use a #define statement to specify this value in a .h file.

// the Facebook Access Token, which can be obtained using the Temboo OAuth Choreos
const String FACEBOOK_ACCESS_TOKEN = "CAAWi1BjpAXgBAKDHIuVI0P8PNFcU5i7KCteChMH3R3G4FtA0H4KNRxJ5nfo0PGCsHqMquCzadZCYsiT0FqZBuOXwKwkQvpurPV7OaRX0E5MYJ2O8iEkDv76CEvSZApfLRFC2yinriu0cWBv5jJ6dmZCMe1jDPzuD5tp7pYyLR5mrCoKqZCzJnleqtSnNiUZCg9VOnALrTInFQZAQY1ZCOVh5";
int numRuns = 1;   // execution count, so this sketch doesn't run forever
int maxRuns = 1;  // the max number of times the Facebook SetStatus Choreo should run

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

long lastMillis;
int count=0;


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  // For debugging, wait until a serial console is connected.
  delay(4000);
  while (!Serial);
  Bridge.begin();
}

void loop() {
  count = 0;
  lastMillis = millis();
 Serial.println("Start");
  while (millis() - lastMillis < 120000) {
    //Serial.println(millis() - lastMillis);
    if (digitalRead(A0)) {
      moveWings();
      count++;
    }
  }
  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {

    // print status
    Serial.println("Running UpdateFacebookStatus - Run #" + String(numRuns++) + "...");

    // Define the status message we want to post on Facebook; since Facebook
    // doesn't allow duplicate status messages, we'll include a changing value.
    String statusMsg = "El Quetzal comienza a comunicarse " + String(millis()) + " milliseconds!";

    // define the Process that will be used to call the "temboo" client
    TembooChoreo SetStatusChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked and repopulated with
    // appropriate arguments each time its run() method is called.
    SetStatusChoreo.begin();

    // set Temboo account credentials
    SetStatusChoreo.setAccountName(TEMBOO_ACCOUNT);
    SetStatusChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SetStatusChoreo.setAppKey(TEMBOO_APP_KEY);

    // tell the Temboo client which Choreo to run (Facebook > Publishing > SetStatus)
    SetStatusChoreo.setChoreo("/Library/Facebook/Publishing/SetStatus");

    // set the required choreo inputs
    // see  https://www.temboo.com/library/Library/Facebook/Publishing/SetStatus/
    // for complete details about the inputs for this Choreo

    SetStatusChoreo.addInput("AccessToken", FACEBOOK_ACCESS_TOKEN);
    SetStatusChoreo.addInput("Message", statusMsg);


    // tell the Process to run and wait for the results. The
    // return code (returnCode) will tell us whether the Temboo client
    // was able to send our request to the Temboo servers
    unsigned int returnCode = SetStatusChoreo.run();

    // print the response code and API response.
    Serial.println("Response code: " + String(returnCode));

    // note that in this case, we're just printing the raw response from Facebook.
    // see the examples on using Temboo SDK output filters at http://www.temboo.com/arduino
    // for information on how to filter this data
    while (SetStatusChoreo.available()) {
      char c = SetStatusChoreo.read();
      Serial.print(c);
    }

    SetStatusChoreo.close();
  }

  Serial.println("Waiting...");
  Serial.println("");

  //delay(30000); // wait 30 seconds between SetStatus calls
}


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
    delay(1 + sq(deg - 90) / 80);
    //Serial.println(deg);
  }
  delay(1000);
  for (uint16_t deg = 90; deg >= 30; deg--) {
    moveDegree(4, deg);
    delay(50 + sq(deg - 90) / 90);
  }
  for (uint16_t deg = 30; deg <= 150; deg++) {
    moveDegree(4, deg);
    delay(50 + sq(deg - 90) / 90);
  }
  for (uint16_t deg = 150; deg >= 90; deg--) {
    moveDegree(4, deg);
    delay(50 + sq(deg - 90) / 90);
  }

  delay(1000);
  for (uint16_t deg = 180; deg > 0; deg--) {
    moveDegree(0, 180 - deg);
    moveDegree(1, deg / 2);
    moveDegree(2, deg);
    moveDegree(3, 90 - deg / 2);
    delay(7 + sq((180 - deg) - 90) / 90);
  }
  delay(1000);



}
