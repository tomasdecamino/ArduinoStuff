// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output & A0 as input.
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int val = analogRead(A0); //reads the potenciometer value
  int intensity = map(val, 0,1023, 0, 255); // changes units
  analogWrite(3, intensity);   // turn the LED
}
