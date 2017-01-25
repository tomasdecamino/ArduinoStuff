//Tpmas de Camino
//Conecta un Relay conectad en pin 5.

#include <GSM.h>
#include<stdlib.h>

#define PINNUMBER "" //numero de pin del SIM
//PHONENUMBER es el numero a donde se envian los reportes
#define PHONENUMBER "87085298"



//clase para el GSM
GSM gsm;
GSM_SMS sms;

String phones[2]={
  "87085298",
  "88989869"
};


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
  pinMode(12,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  digitalWrite(12,LOW);

}

void loop()
{
  if(Serial.available() > 0) {
    int winnerNumber = Serial.parseInt();
    
    if(Serial.read() == '\n') {
      digitalWrite(12,HIGH);
      String winnerStr = "" + winnerNumber;
      char call[8];
      winnerStr.toCharArray(call,9);
      Serial.println(call);
      sms.beginSMS(call);
      sms.print("Arduino Day");
      int r = sms.endSMS(); 
      Serial.println(r);
      digitalWrite(12,LOW);
    }
    
  }
  if(digitalRead(7)==LOW){
    
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







