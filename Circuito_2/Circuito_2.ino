//Tomas de Camino Beck
//Bionica Veritas

void setup() 
{
  //Asigna el pin 13 para salida
  pinMode(13, OUTPUT);	
}


void loop() 
{
  int sensorValue; //preapara una variable para asignar un valor
  sensorValue = analogRead(A0); //lee la entrada analoga A0 del arduino   
  digitalWrite(13, HIGH);  //prende el LED   
  delay(sensorValue);      //espera lo que indique el potenciometro   
  digitalWrite(13, LOW);   //Apaga el LED
  delay(sensorValue);     //espera    
}

