/*
  SendDataToGoogleSpreadsheet

  Demonstrates appending a row of data to a Google spreadsheet from the Arduino Yun 
  using the Temboo Arduino Yun SDK.  

  This example code is in the public domain.
*/



#include <Bridge.h>
#include <Temboo.h>
//#include "TembooAccount.h" // contains Temboo account information

#define TEMBOO_ACCOUNT "tomasdecamino"  // your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // your Temboo app key name
#define TEMBOO_APP_KEY  "f3b65fda220249d8b5a9a3fc84921de7"  // your Temboo app key

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.

const String GOOGLE_USERNAME = "tomas.decamino@gmail.com"; // use your full google email address
const String GOOGLE_PASSWORD = "tomd8786";

// the title of the spreadsheet you want to send data to
// (Note that this must actually be the title of a Google spreadsheet
// that exists in your Google Drive/Docs account, and is configured
// as described above.)
const String SPREADSHEET_TITLE = "tempYun";

int numRuns = 1;   // execution count, so this doesn't run forever
int maxRuns = 100;   // the max number of times the Google Spreadsheet Choreo should run

//date and time info
Process date;        


void setup() {
  
  // for debugging, wait until a serial console is connected
  Serial.begin(9600);
  delay(4000);
  while(!Serial);

  Serial.print("Initializing the bridge... ");
  Bridge.begin();
  Serial.println("Done!\n");
  
  //start the date process
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }
  
  
}

void loop()
{

  // while we haven't reached the max number of runs...
  if (numRuns <= maxRuns) {

    Serial.println("Running AppendRow - Run #" + String(numRuns++));

    // get the number of milliseconds this sketch has been running
    unsigned long now = millis();
    
    Serial.println("Getting sensor value...");

    // get the value we want to append to our spreadsheet
    unsigned long sensorValue = getSensorValue();

    Serial.println("Appending value to spreadsheet...");

    // we need a Process object to send a Choreo request to Temboo
    TembooChoreo AppendRowChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked and repopulated with
    // appropriate arguments each time its run() method is called.
    AppendRowChoreo.begin();
    
    // set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // identify the Temboo Library choreo to run (Google > Spreadsheets > AppendRow)
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");
    
    // set the required Choreo inputs
    // see https://www.temboo.com/library/Library/Google/Spreadsheets/AppendRow/ 
    // for complete details about the inputs for this Choreo
    
    // your Google username (usually your email address)
    AppendRowChoreo.addInput("Username", GOOGLE_USERNAME);

    // your Google account password
    AppendRowChoreo.addInput("Password", GOOGLE_PASSWORD);

    // the title of the spreadsheet you want to append to
    AppendRowChoreo.addInput("SpreadsheetTitle", SPREADSHEET_TITLE);

    // convert the time and sensor values to a comma separated string
    //String rowData(now);
    
    //Getting the process to run to get the time from server
    if (!date.running())  {
      date.begin("date");
      date.addParameter("+%T");
      date.run();
    }
    
    String rowData = date.readString(); 
    rowData += ",";
    rowData += sensorValue;
    Serial.println(rowData);
    // add the RowData input item
    AppendRowChoreo.addInput("RowData", rowData);

    // run the Choreo and wait for the results
    // The return code (returnCode) will indicate success or failure 
    unsigned int returnCode = AppendRowChoreo.run();

    // return code of zero (0) means success
    if (returnCode == 0) {
      Serial.println("Success! Appended " + rowData);
      Serial.println("");
    } else {
      // return code of anything other than zero means failure  
      // read and display any error messages
      while (AppendRowChoreo.available()) {
        char c = AppendRowChoreo.read();
        Serial.print(c);
      }
    }

    AppendRowChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30*60000); // wait 5 seconds between AppendRow calls
}

// this function simulates reading the value of a sensor 
unsigned long getSensorValue() {
  return analogRead(A0);
}
