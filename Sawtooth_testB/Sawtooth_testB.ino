float a = 2;
float p = 0.1;
float t = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  p = map(analogRead(A0), 0, 1023, 1, 10000);
  a = float(map(analogRead(A1), 0, 1023, 1, 100));
  float x = 2 * ((t / a) - floor(0.5 + t / a));
  int val = (1 +  x) / 2 * 255;
 // Serial.println(x);
  analogWrite(9, val);
  t += 0.1;
  delayMicroseconds(p);
  digitalWrite(9, LOW);
  delayMicroseconds(p);

}


