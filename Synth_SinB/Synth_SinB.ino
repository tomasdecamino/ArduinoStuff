#define BIT0 2
#define BIT1 3
#define BIT2 4
#define BIT3 5


int tempo = 0;

//sawtooth
int sintab[500] =
{
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,3,3,3,3,
3,3,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,5,
5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,8,8,8,8,8,8,8,8,8,
8,8,8,8,8,8,8,8,8,8,8,8,
8,8,8,8,8,8,8,8,8,8,8,8,
9,9,9,9,9,9,9,9,9,9,9,9,
9,9,9,9,9,9,9,9,9,9,9,9,
9,9,9,9,9,9,9,9,9,9,10,10,
10,10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,10,10,
10,10,10,10,11,11,11,11,11,
11,11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,11,
11,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,13,
13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,
13,13,14,14,14,14,14,14,14,14,
14,14,14,14,14,14,14,14,14,14,
14,14,14,14,14,14,14,14,14,14,
14,14,14,14,14
};

void setup() {
  // put your setup code here, to run once:
  pinMode(BIT0, OUTPUT);
  pinMode(BIT1, OUTPUT);
  pinMode(BIT2, OUTPUT);
  pinMode(BIT3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int s = map(analogRead(A0), 0, 1023, 1, 200);
  int tempo2 = map(analogRead(A5), 0, 1023, -100, 100);
  stepWave(sintab[tempo]);
  tempo = ((tempo + tempo2) + s) % 500;
}

void stepWave(byte b) {
  digitalWrite(BIT0, bitRead(b, 0));
  digitalWrite(BIT1, bitRead(b, 1));
  digitalWrite(BIT2, bitRead(b, 2));
  digitalWrite(BIT3, bitRead(b, 3));
}

