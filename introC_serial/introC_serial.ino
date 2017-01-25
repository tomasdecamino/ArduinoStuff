void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  Serial.println(analogRead(A0));
}
