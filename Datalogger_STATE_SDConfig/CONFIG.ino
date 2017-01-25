// Code from:
//Saving & Loading Settings on SD Card with Arduino by Alex Shu
//http://overskill.alexshu.com/saving-loading-settings-on-sd-card-with-arduino/
//
void readSDSettings() {
  char character;
  String settingName;
  String settingValue;
  configfile = SD.open("CONFIG.TXT");
  if (configfile) {
    while (configfile.available()) {
      character = configfile.read();
      while ((configfile.available()) && (character != '[')) {
        character = configfile.read();
      }
      character = configfile.read();
      while ((configfile.available()) && (character != '=')) {
        settingName = settingName + character;
        character = configfile.read();
      }
      character = configfile.read();
      while ((configfile.available()) && (character != ']')) {
        settingValue = settingValue + character;
        character = configfile.read();
      }
      if (character == ']') {

          /*
        //Debugging Printing
        Serial.print("Name:");
        Serial.println(settingName);
        Serial.print("Value:");
        Serial.println(settingValue);
           */

        // Apply the value to the parameter
        applySetting(settingName, settingValue);
        // Reset Strings
        settingName = "";
        settingValue = "";
      }
    }
    // close the file:
    configfile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening CONFIG.TXT");
  }
}
/* Apply the value to the parameter by searching for the parameter name
  Using String.toInt(); for Integers
  toFloat(string); for Float
  toBoolean(string); for Boolean
  toLong(string); for Long
*/
void applySetting(String settingName, String settingValue) {
  if (settingName == "CONFIG" && settingValue == "TRUE") {
    CONFIG = true;
  }
  if (settingName == "CONFIG" && settingValue == "FALSE") {
    CONFIG = false;
  }
if (settingName == "SLEEP" && settingValue == "TRUE") {
    SLEEP = true;
  }
  if (settingName == "SLEEP" && settingValue == "FALSE") {
    SLEEP = false;
  }
  if (settingName == "INTERVAL") {
    interval = settingValue.toInt();
  }
  if (CONFIG && (settingName == "YEAR")) {
    rtc.setYear(settingValue.toInt());
  }
  if (CONFIG && settingName == "MONTH") {
    rtc.setMonth(settingValue.toInt());
  }
  if (CONFIG && settingName == "DAY") {
    rtc.setDay(settingValue.toInt());
  }
  if (CONFIG && settingName == "HOURS") {
    rtc.setHours(settingValue.toInt());
  }
  if (CONFIG && settingName == "MINUTES") {
    rtc.setMinutes(settingValue.toInt());
  }
  if (CONFIG && settingName == "SECONDS") {
    rtc.setSeconds(settingValue.toInt());
  }
}

