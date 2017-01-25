//Written by Tomas de Camino Beck
#include <math.h> 
#include <TinyGPS.h>
#define R 6371.009;

TinyGPS gps;

float rad = PI/180; //para cnvertir de grados a radianes

float latitude, longitude;
float lattmp,lontmp;
float distThres =0.0; //para determinar la distancia en km a la que reporte
float dist =0;
int reportTime = 10000;
float velocity;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  bool newdata = false;

  unsigned long start = millis();
  // Update cada segundo
  while (millis() - start < reportTime)
  {
    if (gpsSerial())
      newdata = true;
  }
  //obtener datos del GPS
  getGPS(gps);
  //print to serial para debugging
  if(latitude<90){
    if(dist>=distThres){
     Serial.print(latitude,8);
     Serial.print(',');
     Serial.print(longitude,8);
     Serial.print(',');
     Serial.print((3600000* dist)/(millis()-start),4);
     Serial.println();
    } else {
     Serial.println("no hay movimiento");
    }
  } 
  else{
    Serial.println("No hay datos");
  }
  //delay(reportTime);
}

void getGPS(TinyGPS &gps)
{
  lattmp = latitude;
  lontmp = longitude;
  unsigned long age = 0;
  //obtiene los datos de lat long del gps
  gps.f_get_position(&latitude, &longitude, &age);
  //Calcula distancia
  dist = distance(); 
  gpsSerial();
  velocity = gps.f_speed_kmph();
}



//funcion que checkea si hay datos que leer
static bool gpsSerial()
{
  while (Serial.available())
  {
    if (gps.encode(Serial.read()))
      return true;
  }
  return false;
}

//Calcula la distancia aproximada en Km lineal de dos coordenadas
//proyectando una esfera a un plano
float distance(){
  float lat2 =  latitude *rad;
  float lon2 = longitude *rad;
  float lat1 = lattmp *rad;
  float lon1 = lontmp *rad;
  return sqrt(square(lat2-lat1)+square(cos((lat1+lat2)/2)*(lon2-lon1))) * R;
}

