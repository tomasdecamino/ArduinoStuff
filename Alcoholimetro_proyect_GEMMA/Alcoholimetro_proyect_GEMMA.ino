int mq3_analogPin = 1; // connected to the output pin of MQ3 

void setup(){
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  
}

void loop()
{
  // give ample warmup time for readings to stabilize
  int mq3_value = analogRead(mq3_analogPin);
  if(mq3_value>1022){
    digitalWrite(1,HIGH);
    digitalWrite(0,LOW);

  }else{
    digitalWrite(1,LOW);
    digitalWrite(0,HIGH); 
  }
  delay(500); //Just here to slow down the output.
}
