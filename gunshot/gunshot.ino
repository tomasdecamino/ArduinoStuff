
void setup(){
  pinMode(8,OUTPUT);
  Keyboard.begin();
  pinMode(2,INPUT);
}

void loop(){
  int switchState = digitalRead(2);
  digitalWrite(8,HIGH);
  if(switchState == HIGH){
    Keyboard.press(0xDA);//UP
    delay(200);
    digitalWrite(8,LOW);
    delay(120);
    Keyboard.releaseAll();
    digitalWrite(8,HIGH);
    delay(300);
    Keyboard.press(0xDA);//UP
    delay(200);
    digitalWrite(8,LOW);
    delay(120);
    Keyboard.releaseAll();
    digitalWrite(8,HIGH);
    delay(800);
    Keyboard.press(0xDA);//UP
    delay(200);
    digitalWrite(8,LOW);
    delay(120);
    Keyboard.releaseAll();
    digitalWrite(8,HIGH);
  }
}

