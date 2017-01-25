#include <GSM.h>

#define PINNUMBER "" //incluye tu pin aca, si es prepago dejar en blanco

GSM gsm; // include a 'true' parameter for debug enabled
GSM_SMS sms;

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  //prender el GSM SHield
  GSMpower();

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    Serial.print("connecting...");
    if(gsm.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
 
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println("prueba GSM");

  sms.beginSMS("");//Agregar numero aca
  sms.print("prueba GSM");
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");
}

void loop()
{
// once connected do something interesting
}

void GSMpower()
// equivalente  apretar y soltar el boton
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}
