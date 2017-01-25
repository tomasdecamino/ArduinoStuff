//Tomas de Camino Beck
//Bionica Veritas

void setup() 
{
  //Asigna el pin 10 para salida (pin 10 es PWM)
  pinMode(10, OUTPUT);	
}


void loop() 
{
  int sensorValue; //preapara una variable para asignar un valor
  sensorValue = analogRead(A0); //lee la entrada analoga A0 del arduino   
  //dividimos el valor entre 4 pues las salidas
  //analogas van de 0 a 255 y las entradas de 0 a 1023
  analogWrite(10, sensorValue/4);  //prende el LED con intensidad  
   
}

