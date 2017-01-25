void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(9600);
  analogReadResolution(12); 
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialUSB.println(analogRead(A0));
}
