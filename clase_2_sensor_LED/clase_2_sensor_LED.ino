//Divisor de Voltaje//
int critico =512;//valor critico de cambio de luz

void setup(){
  //Esta funcion solo se ejecuta al inicio del programa
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600); //conecta puerto serial  
}

void loop (){
 //Esta funcion se repite de manera infinita
  int valor = analogRead(A0);//lee el pin A0 y lo almacena en valor
  Serial.println(valor);//manda el valor a puerto serial
  if(valor>critico){
    //si el valor es mayor a entonces apagar led
    digitalWrite(13,LOW);
  }else{
    //si es menor o igual a prender led
    digitalWrite(13,HIGH);
  }
  delay(200);
}
