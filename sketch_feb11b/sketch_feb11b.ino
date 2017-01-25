void setup() {
  // put your setup code here, to run once:

  pinMode(9, OUTPUT);
}

void loop() {
  tone(9,280);
  delay(500);
  noTone(9);
  delay(500);
}
