//Tpmas de Camino
//Conecta un Relay conectad en pin 5.

#include <GSM.h>
#include<stdlib.h>


#define PINNUMBER "" //numero de pin del SIM
//PHONENUMBER es el numero a donde se envian los reportes
#define PHONENUMBER "87085298"
char remoteNumber[20];

//clase para el GSM
GSM gsm;
GSM_SMS sms;

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
    if(gsm.begin()==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("No hay conexion");
      delay(1000);
    }
    
  }

  Serial.println("GSM conectado");
  //elimina cualquier mensaje anterior en el SIM
  sms.flush();
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);

}

void loop()
{


  //verifica si hay mensajes SMS
  char c;
  if (sms.available()){
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
    //obtiene el numero den sender
    sms.remoteNumber(remoteNumber, 20);
    Serial.println(remoteNumber);
    while(c=sms.read()){
      Serial.println(c);
      if(c =='o'||c=='O'){
        Serial.println("On");
        sms.beginSMS(PHONENUMBER);
        sms.print(analogRead(A0));
        sms.endSMS(); 
        Serial.println("\nENVIADO!\n");
        
        analogRead(A0);
      }   
      if(c =='x'||c=='X'){
        Serial.println("Off");
        digitalWrite(5,HIGH);        
      }else{
       break;
      }    
    }
    sms.flush();
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
  digitalWrite(9, HIGH);
}

