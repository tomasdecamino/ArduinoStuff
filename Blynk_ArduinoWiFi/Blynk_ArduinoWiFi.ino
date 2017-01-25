

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <Wire.h>
#include <BlynkSimpleWifiB.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f80b560b9e04454aa57ece63b05065a7";

void setup()
{
  Serial.begin(9600);
  Wifi.begin();
  Wifi.println("WebServer Server is up"); 
  Blynk.begin(auth);
  // Or specify server using one of those commands:
  //Blynk.begin(auth, "cloud.blynk.cc", 8442);
  //Blynk.begin(auth, server_ip, port);
}

void loop()
{
  Blynk.run();
}

