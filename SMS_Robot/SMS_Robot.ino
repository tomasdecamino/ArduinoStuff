#include <GSM.h>
#include<stdlib.h>

const int controlPin1R = 4;
const int controlPin2R = 5;
const int controlPin1L = 6;
const int controlPin2L = 7;
const int enablePinR= 10;
const int enablePinL= 11;

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
  
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(controlPin1R,OUTPUT);
  pinMode(controlPin2R,OUTPUT);
  pinMode(controlPin1L,OUTPUT);
  pinMode(controlPin2L,OUTPUT); 
  pinMode(enablePinR,OUTPUT);
  pinMode(enablePinL,OUTPUT); 
  digitalWrite(enablePinR,LOW);
  digitalWrite(enablePinL,LOW);
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,HIGH);
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);

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
      if(c =='f'||c=='F'){
        mForward(1500);
        mStop();
        Serial.print("Forward");
        delay(500);
      }
      if(c =='b'||c=='B'){
        mBackward(1500);
        mStop();
        Serial.print("Backward");
        delay(500);       
      }     
      if(c =='l'||c=='L'){
        mLeft(1100);
        mStop();
        Serial.print("Left");        
        delay(500);        
      }      
      if(c =='r'||c=='R'){
        mRight(1100);
        mStop();
        Serial.print("Right");        
        delay(500);        
      }else{
        mStop();
      }
    }
    Serial.println("Fin");
    sms.flush(); //borra 
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    //al eviar ? manda las coordenadas

  }
  mStop();
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

void mBackward(int time){
  //motor der
  digitalWrite(controlPin1R,LOW);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,LOW);
  analogWrite(enablePinR,255);
  analogWrite(enablePinL,255);
  delay(time); 
}

void mForward(int time){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,LOW);
  //motor izq
  digitalWrite(controlPin1L,LOW);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinL,249); //los motores no corren igual
  analogWrite(enablePinR,255);
  delay(time);
}

void mRight(int time){
  //motor der
  digitalWrite(controlPin1R,LOW);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,LOW);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinL,255); 
  analogWrite(enablePinR,255);
  delay(time);
}


void mLeft(int time){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,LOW);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,LOW);
  analogWrite(enablePinL,255); 
  analogWrite(enablePinR,255);
  delay(time);
}

void mStop(){
  //motor der
  digitalWrite(controlPin1R,HIGH);
  digitalWrite(controlPin2R,HIGH);
  //motor izq
  digitalWrite(controlPin1L,HIGH);
  digitalWrite(controlPin2L,HIGH);
  analogWrite(enablePinR,LOW);
  analogWrite(enablePinL,LOW); 
}



