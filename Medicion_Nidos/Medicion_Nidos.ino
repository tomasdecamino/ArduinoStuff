void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  SerialUSB.begin(9600);
  analogReadResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  float volt = float(val)/4960 * 3.3;
  SerialUSB.print(val);
  SerialUSB.print(",");
  SerialUSB.println(volt,10);
  delay(50);

  

}
