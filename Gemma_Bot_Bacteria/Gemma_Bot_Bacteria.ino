//Tomas de Camino Beck
//www.funcostarica.org

#define M1 220 //mas para RC
#define M0 220

int luz;


void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  luz = analogRead(2);
  int t = random(luz);
  //moveLeft();
  //delay(t);
  moveRight();
  delay(random(2000));
  moveForward();
  delay(random(2000));
  moveStop();
  delay(t*4);

}

void moveForward() {
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
}

void moveLeft() {
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);
}

void moveRight() {
  digitalWrite(0,HIGH);
  digitalWrite(1, LOW);
}

void moveStop() {
  analogWrite(0, LOW);
  analogWrite(1, LOW);
}


