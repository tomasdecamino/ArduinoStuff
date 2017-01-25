int x,y;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    x = Serial.parseInt();
    y = Serial.parseInt();

  }
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);
}
