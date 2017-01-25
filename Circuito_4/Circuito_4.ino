//Tomas de Camino Beck
//Bionica Veritas

//variable global
int sensorValue = 0; //preapara una variable para asignar un valor

void setup() 
{
  //Asigna el pin 10 para salida (pin 10 es PWM)
  pinMode(10, OUTPUT);	
}


void loop() 
{
  sensorValue = analogRead(A0); //lee la entrada analoga A0 del arduino   
  //dividimos el valor entre 4 pues las salidas
  //analogas van de 0 a 255 y las entradas de 0 a 1023
  
  //Coddigo Morse SOS
  blinkRate(200);
  delay(500);
  blinkRate(500);
  delay(500);
  blinkRate(200);
  delay(1500);
   
}

//funcion para prender la luz por el tiempo rate
void blinkRate(int rate){
  analogWrite(10, sensorValue/4);  //prende el LED con intensidad 
  delay(rate);
  analogWrite(10, 0);
  delay(100);
  analogWrite(10, sensorValue/4);  //prende el LED con intensidad 
  delay(rate);
  analogWrite(10, 0);
  delay(100);
  analogWrite(10, sensorValue/4);  //prende el LED con intensidad 
  delay(rate);
  analogWrite(10, 0);
}
