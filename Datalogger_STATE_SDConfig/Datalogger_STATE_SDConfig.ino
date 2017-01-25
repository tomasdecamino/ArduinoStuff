#include "SD.h"
#include <RTCZero.h>
#include "Adafruit_SI1145.h"

#define SD_LED 8 //SD Card LED
#define SET_CLK 11 // Short to ground to set clock
#define CS 4 // Chip Select pin
#define CD 7 // Card Detect pin

enum STAGE {WAIT, NEW, LOG, SET};
STAGE stage = WAIT;

RTCZero rtc;
Adafruit_SI1145 uv = Adafruit_SI1145();

File logfile;
File configfile;
bool blinkState = false;
String timestamp;
int count = 0;
int interval = 0;
bool CONFIG = false;
bool SLEEP = false;

int seconds = 0;
int minutes = 29;
int hours = 6;
int day = 24;
int month = 3;
int year = 16;

void setup() {
  Serial.begin(115200);
  rtc.begin();
  rtc.setAlarmTime(00, 00, 01);
  rtc.enableAlarm(rtc.MATCH_SS);
  rtc.attachInterrupt(alarmMatch);
  pinMode(SD_LED, OUTPUT);
  digitalWrite(SD_LED, LOW);
  pinMode(CD, INPUT_PULLUP);
  pinMode(SET_CLK, INPUT_PULLUP);
  pinMode(CS, OUTPUT);
  //setClock();
  uv.begin();
}

void loop() {
  if (!digitalRead(SET_CLK)) {
    stage = SET;
  } else if (!cardInserted()) {
    stage = WAIT;
  }
  switch (stage) {
    case WAIT:
      Serial.println("WAIT");
      if (cardInserted()) {
        digitalWrite(SD_LED, LOW);
        stage = NEW;
      } else {
        blinkLED(SD_LED, 500);
      }
      break;
    case NEW:
      Serial.println("NEW");
      if (initSDCard()) {
        count = 0;
        stage = LOG;
      } else {
        stage = WAIT;
      }
      break;
    case LOG:
      Serial.println("LOG");
      if (count == 0) {
        logData();
      }
      if (SLEEP) {
        Serial.println("Sleep");
        rtc.standbyMode();
      }
      count++;
      if (count >= interval) {
        count = 0;
      }
      break;
    case SET:
      Serial.println("SET");
      setClock();
      stage = WAIT;
      break;
    default:
      break;
  }
}

void blinkLED(int led, int t) { //Blink led every t milliseconds
  if (millis() % t > t / 2) { //50% duty cycle
    blinkState = true;
  } else {
    blinkState = false;
  }
  digitalWrite(SD_LED, blinkState);
}

String getTimestamp() {
  String t;
  //t = String(rtc.getEpoch());
  //t = "20" + String(rtc.getYear()) + String(rtc.getMonth()) + String(rtc.getDay()) + String(rtc.getHours()) + String(rtc.getMinutes()) + String(rtc.getSeconds());
  // MM/DD/YYYY HH:MM:SS
  t = String(rtc.getMonth()) + "/" + String(rtc.getDay()) + "/" + "20" + String(rtc.getYear()) + " " + String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" + String(rtc.getSeconds());
  return t;
}
void alarmMatch() {
  Serial.println("Awake!!");
}

