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


void setup()
{
  pinMode(ledPower,OUTPUT);
  //pinMode(A0,INPUT);
  Serial.begin(9600);
  ppm =0;
}

void loop()
{
  unsigned long start = millis();
  // Update cada segundo
  while (millis() - start < reportTime)
  {
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
  float v = (float)dustVal/1023*5;
  //particulas por 0.01 pie cubico
  float p =(v-0.0356)*12000000;
  //particulas por cent'imetro c'ubico
  Serial.println((p*0.0283168)/1000000,5); 
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



