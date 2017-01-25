//modificado por Tomas de Camino Beck

#include <GSM.h>
#include <TinyGPS.h>

#define PINNUMBER "1234"

TinyGPS gps;
GSM gsmAccess; 
GSM_SMS sms;

static void gpsdump(TinyGPS &gps);
static bool feedgps();

void setup()
{
  Serial.begin(9600);
    // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
}

void loop()
{
  bool newdata = false;
  unsigned long start = millis();
  // Update cada segundo
  while (millis() - start < 1000)
  {
    if (feedgps())
      newdata = true;
  }
  //obtener datos del GPS
  gpsdump(gps);
}

static void gpsdump(TinyGPS &gps)
{
  float flat, flon;
  unsigned long age = 0;
  //obtiene los datos de lat long del gps
  gps.f_get_position(&flat, &flon, &age);
  Serial.print(flat,DEC);
  Serial.print(',');
  Serial.print(flon,DEC);
  Serial.println();
  feedgps();
}



//funcion que checkea si hay datos que leer
static bool feedgps()
{
  while (Serial.available())
  {
    if (gps.encode(Serial.read()))
      return true;
  }
  return false;
}
