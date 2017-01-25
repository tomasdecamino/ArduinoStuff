int mq3_analogPin = A0; // connected to the output pin of MQ3 

void setup(){
  Serial.begin(9600); // open serial at 9600 bps
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  
}

void loop()
{
  // give ample warmup time for readings to stabilize
  int mq3_value = analogRead(mq3_analogPin);
  Serial.println(mq3_value);
  if(mq3_value>800){
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
  }else{
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW); 
  }
  
  digitalWrite(8,HIGH);
  delay(500); //Just here to slow down the output.
  digitalWrite(8,LOW);
}
