// @author Tomas de Camino Beck
// www.inventoria.org

#define TIME 2000

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

}

void loop() {
  moveLeft(TIME);
  moveRight(TIME);
  for (int i = 0; i < 10; i++) {
    moveLeft(200);
    moveRight(200);
  }
}

void moveLeft(int time) {
  digitalWrite(0, HIGH);
  delay(time);
  digitalWrite(0, LOW);
}

void moveRight(int time) {
  digitalWrite(1, HIGH);
  delay(time);
  digitalWrite(1, LOW);
}


