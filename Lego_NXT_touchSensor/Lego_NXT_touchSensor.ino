void setup() {
 //pinMode(2,INPUT_PULLUP);
 pinMode(A0,INPUT);
 Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
  delay(100);

}
