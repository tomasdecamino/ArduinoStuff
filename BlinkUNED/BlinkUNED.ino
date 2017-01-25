
void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  int T=analogRead(A0);
  Serial.println(T);
  int val = map(T,0,1023,0,255);
  // put your main code here, to run repeatedly:
  analogWrite(9,val);
}
