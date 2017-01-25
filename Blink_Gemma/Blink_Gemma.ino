//Gemma Blink


int led = 1; // blink 'digital' pin 1 - AKA the built in red LED

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);


}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(led, 60); 
    delay(500);
    digitalWrite(led, LOW);
    delay(5000);
}
