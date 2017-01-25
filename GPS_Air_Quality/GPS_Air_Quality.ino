//Written by Tomas de Camino Beck
#include <math.h> 
#include <TinyGPS.h>
#include <Wire.h>
#include <Adafruit_LSM303.h>
#define R 6371.009;
#include <SPI.h>
#include <SD.h>

Adafruit_LSM303 lsm;

TinyGPS gps;

float rad = PI/180; //para cnvertir de grados a radianes

float latitude, longitude;
float lattmp,lontmp;
float distThres =0.0; //para determinar la distancia en km a la que reporte
float dist =0;
int reportTime = 1000;
float velocity;
//dust sensor
int dustPin=A1;
int ledPower=8;
int delayTime=280;
int delayTime2=40;
float offTime=9680;
int dustVal=0;
float ppm=0;
int count=0;

const int chipSelect = 4;

void setup()
{

  //verifica la tarjeta SD

  /* if (!SD.begin(chipSelect)) {
   Serial.println("Card failed, or not present");
   // don't do anything more:
   return;
   }
   
   File dataFile = SD.open("datalog.txt", FILE_WRITE);
   dataFile.println("lat,long,vel,AQ,x,y,z");
   dataFile.close();*/


  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  pinMode(ledPower,OUTPUT);
  //pinMode(A0,INPUT);
  Serial.begin(9600);
  ppm =0;
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

  //obtiene dust read
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(delayTime);
  dustVal=analogRead(dustPin); // read the dust value
  ppm = ppm+dustVal;
  //Serial.println(ppm);
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(offTime);  
  //obtener datos del GPS
  getGPS(gps);
  lsm.read();
  //print to serial para debugging
  if(latitude<90){
    if(dist>=distThres){
      Serial.print(count);
      Serial.print(',');
      Serial.print(latitude,8);
      Serial.print(',');
      Serial.print(longitude,8);
      Serial.print(',');
      Serial.print((3600000* dist)/(millis()-start),4);
      Serial.print(',');
      Serial.print(ppm);
      Serial.print(',');
      Serial.print((int)lsm.accelData.x);
      Serial.print(",");
      Serial.print((int)lsm.accelData.y);
      Serial.print(",");
      Serial.println((int)lsm.accelData.z); 
      count++;     
    } 
    else {
      Serial.println("no hay movimiento");
    }
  } 
  else{
    Serial.println("No hay datos");
  }
  ppm=0;
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








