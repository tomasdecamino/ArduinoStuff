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

String phones[81]={
"88678756", 
"89387236",
"88100748",
"89197448",
"88379436",
"88355976",
"71032250",
"83579308",
"87083232",
"87204188",
"85086647",
"83109168",
"83724217",
"83873467",
"70181770",
"88509624",
"83804697",
"88845113",
"70137515",
"84058330",
"88863344",
"60061629",
"89250915",
"88282501",
"87188763",
"86678480",
"83263581",
"61034261",
"60957364",
"87430717",
"86419101",
"84847690",
"88722847",
"88333344",
"88381368",
"89607648",
"85691229",
"70319609",
"88542604",
"88595732",
"88224785",
"87106624",
"87066984",
"87559825",
"86110700",
"89630073",
"88810017",
"62154065",
"89894511",
"60480889",
"88415823",
"87216592",
"88735199",
"89821212",
"89919527",
"89877396",
"70101099",
"85604334",
"85495791",
"84213493",
"88611737",
"61827374", 
"83165070",
"60376545",
"88839834",
"89971198",
"61341320",
"88361685",
"61275702",
"83280251",
"83376058",
"83316125",
"89312786",
"88696162",
"86985216",
"83226044",
"83139073",
"88845809",
"86645626",
"89904598",
"83105904"
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
  if(digitalRead(7)==LOW){
    digitalWrite(12,HIGH);
    int p = (int) random(81);
    char call[8];
    phones[p].toCharArray(call,9);
    Serial.println(call);
    sms.beginSMS(call);
    sms.print("Arduino Day");
    int r = sms.endSMS(); 
    Serial.println(r);
    digitalWrite(12,LOW);
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







