void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  int valor = digitalRead(12);
  Serial.println(valor);
  if (valor == 0){
    digitalWrite(13, HIGH);
    delay(50);
  } else {
    digitalWrite(13, LOW);
    delay(50);
  }

}
