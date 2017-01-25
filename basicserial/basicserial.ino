void setup() {
  // put your setup code here, to run once:
 // analogReadResolution(12);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
}
