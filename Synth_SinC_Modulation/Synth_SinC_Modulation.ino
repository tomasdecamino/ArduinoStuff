#define BIT0 2
#define BIT1 3
#define BIT2 4
#define BIT3 5

#define BIT0B 8
#define BIT1B 9
#define BIT2B 10
#define BIT3B 11

int tempo = 0;
int tempo2 = 0;

//sawtooth
int sintab[500] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10,
  10, 10, 10, 10, 10, 10, 10, 10, 10,
  10, 10, 10, 10, 10, 10, 10, 10, 10,
  10, 10, 10, 10, 10, 10, 10, 10, 10,
  10, 10, 10, 10, 11, 11, 11, 11, 11,
  11, 11, 11, 11, 11, 11, 11, 11, 11,
  11, 11, 11, 11, 11, 11, 11, 11, 11,
  11, 11, 11, 11, 11, 11, 11, 11, 11,
  11, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 13,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 14, 14, 14, 14, 14, 14, 14, 14,
  14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
  14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
  14, 14, 14, 14, 14
};

void setup() {
  // primer OSC
  pinMode(BIT0, OUTPUT);
  pinMode(BIT1, OUTPUT);
  pinMode(BIT2, OUTPUT);
  pinMode(BIT3, OUTPUT);
  //segundo OSC
  pinMode(BIT0B, OUTPUT);
  pinMode(BIT1B, OUTPUT);
  pinMode(BIT2B, OUTPUT);
  pinMode(BIT3B, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int s = map(analogRead(A0), 0, 1023, 1, 100);
  int mod = map(analogRead(A5), 0, 1023, 0, 10);
  int mod2 = map(analogRead(A4), 0, 1023, 1, 10);
  int mod3 = map(analogRead(A3), 0, 1023, 1, 10);
  stepWave(sintab[tempo]*mod3);
  stepWaveB(sintab[tempo]+mod*mod2);
  tempo = (tempo + s) % 500;
  //tempo2=(tempo+s + mod)%500;
}

void stepWave(byte b) {
  digitalWrite(BIT0, bitRead(b, 0));
  digitalWrite(BIT1, bitRead(b, 1));
  digitalWrite(BIT2, bitRead(b, 2));
  digitalWrite(BIT3, bitRead(b, 3));
}

void stepWaveB(byte b) {
  digitalWrite(BIT0B, bitRead(b, 0));
  digitalWrite(BIT1B, bitRead(b, 1));
  digitalWrite(BIT2B, bitRead(b, 2));
  digitalWrite(BIT3B, bitRead(b, 3));
}

