
/*
  Simple RTC Alarm for Adafruit Feather M0 modified from
  RTCzero library example by Arturo Guadalupi
  By: CaveMoa
  Date: 19/12/15
*/

#include <RTCZero.h>

/* Create an rtc object */
RTCZero rtc;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // turn the LED on
  delay(50);
  digitalWrite(13, LOW);    // turn the LED off
  rtc.begin();
    rtc.setAlarmSeconds(30); 
  rtc.enableAlarm(rtc.MATCH_SS); 
  rtc.attachInterrupt(alarmMatch);

}

void loop()
{

  rtc.standbyMode();    


  digitalWrite(13, HIGH);   // turn the LED on
  delay(2000);
  digitalWrite(13, LOW);    // turn the LED off

}

void alarmMatch() {


}

