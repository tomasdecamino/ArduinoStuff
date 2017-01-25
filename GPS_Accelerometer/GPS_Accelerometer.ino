//Written by Tomas de Camino Beck
#include <math.h> 
#include <TinyGPS.h>
#define R 6371.009;

TinyGPS gps;

//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minX = 267;
int maxX = 404;
int minY = 268;
int maxY = 404;
int minZ = 264;
int maxZ = 398;


float rad = PI/180; //para cnvertir de grados a radianes

float latitude, longitude;
float lattmp,lontmp;
float distThres =0.0; //para determinar la distancia en km a la que reporte
float dist =0;
int reportTime = 1000;
float velocity;

void setup()
{
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW); 
  Serial.println("lat,long,speed,xg,yg,zg,millis"); 
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
  //read the analog values from the accelerometer
  long xRead = map(analogRead(xPin),minX,maxX,-1000,1000);
  long yRead = map(analogRead(yPin),minY,maxY,-1000,1000);
  long zRead = map(analogRead(zPin),minZ,maxZ,-1000,1000);
  //print to serial para debugging
  if(latitude<90){
    if(dist>=distThres){
     Serial.print(latitude,8);
     Serial.print(',');
     Serial.print(longitude,8);
     Serial.print(',');
     Serial.print(velocity);
     Serial.print(',');
     Serial.print(xRead);
     Serial.print(',');
     Serial.print(yRead);
     Serial.print(',');
     Serial.print(zRead);
     Serial.print(',');
     Serial.println(millis()-start);
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

