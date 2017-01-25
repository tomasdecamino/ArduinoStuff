void setup(){
  pinMode(9,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int val = analogRead(A0);
  int val2 =1000- map(analogRead(A1),0,1023,0,1000);
  int mapval = 50-map(val,0,1023,1,50);
  Serial.println(val2);
  analogWrite(9,(255/2*(1+sin(millis()*1/val2))));
  delay(mapval);
  digitalWrite(9,LOW);
  delay(mapval);


}

