int count = 0; //variable par contar
int newTilt, lastTilt=0;

void setup(){
 pinMode(9,OUTPUT);//El LED
 pinMode(8,INPUT); // El sensor de inclinacion
 Serial.begin(9600);
  
}


void loop(){
  count += !(newTilt == lastTilt); //cuenta el cambio en inclinación
  lastTilt = newTilt;
  newTilt=digitalRead(8);
  Serial.println(count);
  //ejemplo, cuando el conteo es 
  //menor a 20 apaga el LED
  if(count<20){
    noTone(9);
  }
  //cuando el conteo es > 20 prende
  if(count>20){
    tone(9,440);
  }
  //cuando es mayor a 40 apaga y resetea el conteo
  if(count>40){
   tone(9,880);
  }
 if(count>80){
   count = 0;
  }  
}

