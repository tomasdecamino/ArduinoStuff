#include <SPI.h>
#include <YunClient.h>
#include <PubSubClient.h>
 
 
/* ------------------ */
/* SKETCH CREDENTIALS */
/* ------------------ */
 
char* deviceId     = "use-token-auth";             // * set your device id (will be the MQTT client username)
char* deviceSecret = "vUGjLxaAUgZcN0I6+)";         // * set your device secret (will be the MQTT client password)
char* outTopic     = "iot-2/evt/sound/fmt/json"; // * MQTT channel where physical updates are published
char* inTopic      = ""; // * MQTT channel where lelylan updates are received
char* clientId     = "d:ohp9ap:audio:audio-sensor1";             // * set a random string (max 23 chars, will be the MQTT client id)
  
 
/* ------------ */
/* SKETCH LOGIC */
/* ------------ */
 
/* Server settings */
byte server[] = { 23, 246, 232, 210 }; // MQTT server address
 
/* Sample payload published to lelylan */
/* The id is the status property id of the basic light /*
/* http://lelylan.github.io/types-dashboard-ng/#/types/518be107ef539711af000001/ */ 
//char* payloadOn  = "{\"properties\":[{\"id\":\"518be5a700045e1521000001\",\"value\":\"on\"}]}";
//char* payloadOff = "{\"properties\":[{\"id\":\"518be5a700045e1521000001\",\"value\":\"off\"}]}";
 
/* Yun configuration */
byte mac[] = { 0xA0, 0xA0, 0xBA, 0xAC, 0xAE, 0x12 };
YunClient yun;
 
/* MQTT communication */
void callback(char* topic, byte* payload, unsigned int length); // subscription callback
PubSubClient client(server, 1883, callback, yun);         // mqtt client
 
/* Pins configuration */
int inPin = A0; // mic
 
 
/* arduino setup */
void setup() {
  Serial.begin(9600);
  delay(500);
 
  Serial.println("Start initialization of Yun...");
  Bridge.begin();
  Serial.println("Bridge finished setup");
  Serial.println("Starting connection to lelylan...");
 
  MQTTConnection();      // MQTT server connection
  pinMode(inPin, INPUT);    // button pin setup
}
 
/* arduino loop */
void loop() {
  //MQTTConnection();
  char* value="10";
  MQTTPublish("10");
  delay(500);
}
 
/* MQTT server connection */
void MQTTConnection() {
  // add reconnection logics
  while (!client.connected()) {
    // connection to MQTT server
    if (client.connect(clientId, deviceId, deviceSecret)) {
      Serial.println("[PHYSICAL] Successfully connected with MQTT");
    }else{
      Serial.println("[PHYSICAL] Failed MQTT connection");
    }
  }
  client.loop();
}
 
/* MQTT publish */
void MQTTPublish(char* value) {
  client.publish(outTopic, value); // light off
}
 
/* Receive Lelylan message and confirm the physical change */
void callback(char* topic, byte* payload, unsigned int length) {
 /* // copu the payload content into a char*
  char* json;
  json = (char*) malloc(length + 1);
  memcpy(json, payload, length);
  json[length] = '\0';
 
  // update the physical status and confirm the executed update
  if (String(payloadOn) == String(json)) {
    Serial.println("[LELYLAN] Led turned on");
    lelylanPublish("on");
    state = HIGH;
  } else {
    Serial.println("[LELYLAN] Led turned off");
    lelylanPublish("off");
    state = LOW;
  }
 
  digitalWrite(outPin, state);
  free(json);*/
  Serial.println("Callback");
}
