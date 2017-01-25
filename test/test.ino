void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  if (analogRead(A0) > 200) {
    Mouse.click();
  }
}
