//Ejemplo Sistema de Control sencillo
//Tomas de Camino Beck
//Pin 8 conectado a un Relay que conecta a un bombillo de 25W
//A0 conectado a un medidor de temperatura.

int ledPin = 8;
int volt, time;
float degreesC;


void setup()
{
  pinMode(ledPin, OUTPUT); 
 Serial.begin(9600);
 time = 100;
}

void loop()
{
  
  //prende y apaga el relay
  //relay en modo Normally closed
  //con HIGH se apaga
  digitalWrite(ledPin, HIGH);   
  delay(2000-time);                  
  digitalWrite(ledPin, LOW);    
  delay(time);                  
  
  //lee el voltage y lo convierte a temperatura
  volt =analogRead(A0);
  degreesC = (volt* 0.004882814 - 0.5) * 100.0;
  Serial.print(time);
  Serial.print(",");
  Serial.println(degreesC);

  //simple rutina de control
  if(degreesC<31){
   time=1500; 
  }else{
   time=0; 
  }
}

