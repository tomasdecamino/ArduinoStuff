void setup(){
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP); 

  pinMode(13,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop(){
  if(digitalRead(2)==LOW){
    digitalWrite(13,HIGH);
    digitalWrite(11,HIGH);   

  }
  else{
    digitalWrite(13,LOW);
    digitalWrite(11,LOW);    
  }

}

