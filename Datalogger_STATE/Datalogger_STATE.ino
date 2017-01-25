
#include "SD.h"
#include "Wire.h"
#include  "RTCZero.h"
#include "Adafruit_SI1145.h"

#define SD_LED 8 //SD Card LED
#define SET_CLK 11 // Short to ground to set clock
#define CS 4 // Chip Select pin
#define CD 7 // Card Detect pin

enum STAGE {WAIT, NEW, LOG, SET};
STAGE stage = WAIT;

Adafruit_SI1145 uv = Adafruit_SI1145();

RTCZero rtc;

File logfile;
int16_t ax, ay, az;
int16_t gx, gy, gz;
bool blinkState = false;
String timestamp;
int count = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  uv.begin();
  pinMode(SD_LED, OUTPUT);
  digitalWrite(SD_LED, LOW);
  pinMode(CD, INPUT_PULLUP);
  pinMode(SET_CLK, INPUT_PULLUP);
  pinMode(CS, OUTPUT);
  //setClock();
}

void loop() {
  if (!digitalRead(SET_CLK)) {
    stage = SET;
  } else
  if (!cardInserted()) {
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
        stage = LOG;
      } else {
        stage = WAIT;
      }
      break;
    case LOG:
      Serial.println("LOG");
      logData();
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
  t = "20" + String(rtc.getYear()) + String(rtc.getMonth()) + String(rtc.getDay()) + String(rtc.getHours()) + String(rtc.getMinutes()) + String(rtc.getSeconds());
  return t;
}

