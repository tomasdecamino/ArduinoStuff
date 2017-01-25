#define IN1 A0
#define IN2 A1
#define OUT1 5
#define OUT2 6

int freq,wave;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  freq = analogRead(IN1);
  wave = analogRead(IN2);
  int conv = map(wave, 0, 1023, 0, 255);
  CV(freq);
  analogWrite(9, conv);
  Serial.print(freq);
  Serial.print(",");
  Serial.println(conv);
}

void CV(int v) {
  int r = map(v, 0, 1023, -255, 255);
  analogWrite(OUT1, max(LOW, -r));
  analogWrite(OUT2, max(LOW, r));

}



