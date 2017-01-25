#define A0T 700
#define A1T 700
#define A2T 700


void setup() {
  // put your setup code here, to run once:

  Keyboard.begin();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your mainasas code here, to run repeatedly:asasasasasasas
  Serial.print(analogRead(A0));
  Serial.print(',');
  Serial.print(analogRead(A1));
  Serial.print(',');
  Serial.println(analogRead(A2));
  if((analogRead(A0) > A0T)&(analogRead(A1) > A1T)){
    Keyboard.press('d');
  }
  else{ 
    if (analogRead(A0) > A0T) {
      Keyboard.press('a');
    }
    if (analogRead(A1) > A1T) {
      Keyboard.press('s');
    }
  }
  delay(500);
  Keyboard.releaseAll();

}

