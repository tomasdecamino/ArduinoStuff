/*
   @author  Tomás de Camino Beck
   www.inventoria.org
*/
void setup() {
  pinMode(A0,INPUT); //initialize pin A0 as input
  pinMode(2,INPUT_PULLUP);//initialize pin 2 as pullup
  pinMode(13,OUTPUT);//initialize pin 13 as output
  Serial.begin(9600); //prepare serial port
}

void loop() {
  digitalWrite(13, HIGH);
  int val = analogRead(A0);
  int boton = digitalRead(2);
  Serial.print(val);
  Serial.print(",");
  Serial.println(boton);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13,LOW);

}
