//Gemma motor


int motor = 0; //motor

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(motor, OUTPUT);


}

void loop() {
    digitalWrite(motor, HIGH); 
    delay(500);
    digitalWrite(motor, LOW);
    delay(500);
}
