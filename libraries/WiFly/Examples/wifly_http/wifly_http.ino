
 
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include "HTTPClient.h"

#define SSID      "SEEED-MKT"
#define KEY       "depot0510"
// WIFLY_AUTH_OPEN / WIFLY_AUTH_WPA1 / WIFLY_AUTH_WPA1_2 / WIFLY_AUTH_WPA2_PSK
#define AUTH      WIFLY_AUTH_WPA2_PSK

#define HTTP_GET_URL "http://httpbin.org/get?hello=world"
#define HTTP_POST_URL "http://httpbin.org/post"
#define HTTP_POST_DATA "Hello world!"

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(2, 3);
WiFly wifly(uart);
HTTPClient http;
char get;

void setup() {
  Serial.begin(9600);    
  Serial.println("------- WIFLY HTTP --------");
  
  
  uart.begin(9600);         // WiFly UART Baud Rate: 9600
  // Wait WiFly to init
//  delay(3000);

  // check if WiFly is associated with AP(SSID)
  if (!wifly.isAssociated(SSID)) {
    while (!wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 0.1 second and try again...");
      delay(100);
    }
    
    wifly.save();    // save configuration, 
  }


  Serial.println("\r\nTry to get url - " HTTP_GET_URL);
  Serial.println("------------------------------");
  while (http.get(HTTP_GET_URL, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    Serial.print(get);
  }

  Serial.println("\r\n\r\nTry to post data to url - " HTTP_POST_URL);
  Serial.println("-------------------------------");
  while (http.post(HTTP_POST_URL, HTTP_POST_DATA, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    Serial.print(get);
  }
   
  if (wifly.commandMode()) {
    Serial.println("\r\n\r\nEnter command mode. Send \"exit\"(with \\r) to exit command mode");
  }
}


void loop() {
  int c;
  while (wifly.available()) {
    c = wifly.read();
    if (c > 0) {
      Serial.write((char)c);
    }
  }
  
  while (Serial.available()) {
    c = Serial.read();
    if (c >= 0) {
      wifly.write((char)c);
    }
  }
}
