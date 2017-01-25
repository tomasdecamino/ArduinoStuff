/**************************************************
 * written by Tomas de Camino
 * some parts of the code are adapted from GSM & GPS 
 * libraries examples from arduino page
 ***************************************************/

#include <GSM.h>
#include <TinyGPS.h>
#include<stdlib.h>

#define PINNUMBER "" //numero de pin del SIM
//PHONENUMBER es el numero a donde se envian los reportes
#define PHONENUMBER "88888888"
char remoteNumber[20];

#define R 6371.009; //radio de la tierra
float latitude, longitude; //lectura actual de latitud longitud
float lattmp,lontmp; //almacena la posicicon anterior
float rad = PI/180; //para cnvertir de grados a radianes
float dist =0;

//opciones para mensaje
unsigned long timeThresh; //intervalo de reportes
unsigned long last;      // medida de tiempo
boolean autoSMS = false; //true para enviar mensajes de manera automatica

//clase para el GSM
GSM gsm;
GSM_SMS sms;

//clase para el GPS
TinyGPS gps;


void setup()
{

  Serial.begin(9600);
  //prender el GSM SHield
  GSMpower();

  // INICIA GSM tomado y adaptado de GSM arduino example
  boolean notConnected = true;
  while(notConnected)
  {
    Serial.print("conectando...");
    if(gsm.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("No hay conexion");
      delay(1000);
    }
    last =  millis();
    timeThresh = 2 * 60000;
  }

  Serial.println("GSM conectado");
  //elimina cualquier mensaje anterior en el SIM
  sms.flush();

}

void loop()
{
  bool newdata = false;
  unsigned long start = millis();
  // Update cada 2 segundos
  while (millis() - start < 2000)
  {
    if (gpsSerial())
      newdata = true;
  }
  getGPS(gps); //obtiene los datos GPS

  //para enviar reportes a itervalos de timeThresh
  if(autoSMS){
    if(millis()-last > timeThresh){
      Serial.println("Enviando...");
      Serial.println(toString(latitude,longitude));
      sms.beginSMS(PHONENUMBER);
      sms.print(toString(latitude,longitude));
      sms.endSMS(); 
      Serial.println("\nENVIADO!\n");
      last = millis();
    }
  }


  //verifica si hay mensajes SMS
  char c;
  if (sms.available())
  {
    //obtiene el numero den sender
    sms.remoteNumber(remoteNumber, 20);
    Serial.println(remoteNumber);
    c=sms.read();  //lee el mensaje solo nos interesa la primera letra
    sms.flush(); //borra el resto  
    //al eviar ? manda las coordenadas
    if(c =='?'){
      Serial.println("Enviando...");
      Serial.println(toString(latitude,longitude));
      sms.beginSMS(remoteNumber);
      sms.print(toString(latitude,longitude));
      sms.endSMS(); 
      Serial.println("\nENVIADO!\n");
    }
    //al enviar un D env'ia la distancia desde el movimiento anterior
    if(c =='D'){
      Serial.println("Enviando...");
      Serial.println(dist);
      sms.beginSMS(remoteNumber);
      char dtxt[12];
      dtostrf(dist,3,4,dtxt);
      sms.print(dtxt);
      sms.endSMS(); 
      Serial.println("\nENVIADO!\n");
    }
    // Para reportes cada 2 min
    if(c == 'F'){
      autoSMS = true;
      timeThresh = 120000; 
    }
    // Para reportes cada 10 min
    if(c == 'M'){
      autoSMS = true;
      last = millis();
      timeThresh = 10  * 60000; 
    }
    //Para reportes cada 30 min
    if(c == 'S'){
      autoSMS = true;
      last = millis();
      timeThresh = 30* 60000; 
    }
    // Apagar los reportes
    if(c == 'N'){
      autoSMS = false;
      last = millis();
      timeThresh = 120000; 
    }
  }

}


//************* Funciones del GSM *****************
//***********************************************
void GSMpower()
// equivalente  apretar y soltar el boton
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}

//envia el mensaje SMS
void latlongSMS(float lat, float lon){
  Serial.println("Enviando...");
  Serial.println();
  sms.beginSMS(PHONENUMBER);
  sms.print(toString(lat,lon));
  sms.endSMS(); 
  Serial.println("\nENVIADO!\n");
}

// prepara el formato del mensaje para
//enviarlo cmo link de google maps
String toString(float lat, float lon){
  String msg;
  char txtlat[12];
  char txtlon[12];
  //convertir float a str  
  dtostrf(lat,3,6,txtlat);
  dtostrf(lon,3,6,txtlon);
  //construye el mensaje de texto con lat long
  msg += "http://maps.google.com/?q=";
  msg += txtlat;
  msg += ",";
  return msg += txtlon;
}

//************** Funciones del GPS ******************
//*************************************************
static void getGPS(TinyGPS &gps)
{
  lattmp = latitude;
  lontmp = longitude;
  unsigned long age = 0;
  //obtiene los datos de lat long del gps
  gps.f_get_position(&latitude, &longitude, &age);
  if(latitude>90){
    Serial.println("No Fix");
  }
  else{
    Serial.print(latitude,DEC);
    Serial.print(',');
    Serial.print(longitude,DEC);
    Serial.println();
  }
  //Calcula distancia
  dist = distance(); 
  gpsSerial();
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
//es una aproximacion que no considera el relieve
// funciona para distancias cortas
float distance(){
  float lat2 =  latitude *rad;
  float lon2 = longitude *rad;
  float lat1 = lattmp *rad;
  float lon1 = lontmp *rad;
  return sqrt(square(lat2-lat1)+square(cos((lat1+lat2)/2)*(lon2-lon1))) * R;
}







