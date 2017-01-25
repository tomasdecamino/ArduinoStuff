void setup() {

  pinMode(A0, INPUT);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  //if the button is pressed
  Serial.println(analogRead(A0));
  if (analogRead(A0) > 400) {
    //Send the message
    Keyboard.write('b');
    delay(200);
    //Keyboard.releaseAll();//
  }
}
