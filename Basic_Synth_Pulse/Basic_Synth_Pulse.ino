void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9,HIGH);
  delayMicroseconds(40000);
  digitalWrite(9,LOW);
}
