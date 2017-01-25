//trigger filename and pin#
#define T00 3
#define T01 4
#define T02 5
#define T03 6
#define T04 7
#define T05 8
#define T06 9
#define T07 10
#define T08 11
#define T09 12
#define T10 13

//tempo for sequence
int tempo = 350;
int p = 0;

void setup() {

  //sync out pin
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // trigger pins
  pinMode(T00, OUTPUT);
  pinMode(T01, OUTPUT);
  pinMode(T02, OUTPUT);
  pinMode(T03, OUTPUT);
  pinMode(T04, OUTPUT);
  pinMode(T05, OUTPUT);
  pinMode(T06, OUTPUT);
  pinMode(T07, OUTPUT);
  pinMode(T08, OUTPUT);
  pinMode(T09, OUTPUT);
  pinMode(T10, OUTPUT);
  digitalWrite(T00, HIGH);
  digitalWrite(T01, HIGH);
  digitalWrite(T02, HIGH);
  digitalWrite(T03, HIGH);
  digitalWrite(T04, HIGH);
  digitalWrite(T05, HIGH);
  digitalWrite(T06, HIGH);
  digitalWrite(T07, HIGH);
  digitalWrite(T08, HIGH);
  digitalWrite(T09, HIGH);
  digitalWrite(T10, HIGH);

  //tempo potentiometer
  pinMode(A0, INPUT);
  //pattern pot
  pinMode(A1, INPUT);

  //5V for pots
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  //ground for pots
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  // Serial.begin(9600);
}

void loop() {
  //get tempo and pattern
  tempo = map(analogRead(A0), 0, 1023, 1000, 130);
  p = map(analogRead(A1), 0, 1023, 21, 0);
  //Serial.println(analogRead(A1));
  //play pattern
  pattern(p);
}

void trigger(int pin) {
  //sync out
  digitalWrite(2, HIGH);
  delay(10);
  digitalWrite(2, LOW);

  digitalWrite(pin, LOW);
  delay(tempo);
  digitalWrite(pin, HIGH);

}

void pattern(int n) {
  switch (n) {
    case 0: pt0(); break;
    case 1: pt1(); break;
    case 2: pt2(); break;
    case 3: pt3(); break;
    case 4: pt4(); break;
    case 5: pt5(); break;
    case 6: pt6(); break;
    case 7: pt7(); break;
    case 8: pt8(); break;
    case 9: pt9(); break;
    case 10: pt10(); break;
    case 11: pt11(); break;
    case 12: pt12(); break;
    case 13: pt13(); break;
    case 14: pt14(); break;
    case 15: pt15(); break;
    case 16: pt16(); break;
    case 17: pt17(); break;
    case 18: pt18(); break;
    case 19: pt19(); break;
    case 20: pt20(); break;
    case 21: pt21(); break;
  }

}

//patterns 5 to 20 where generated randomly

void pt0() {
  delay(tempo * 4);
}

void pt1() {
  trigger(T00);
  trigger(T01);
  trigger(T00);
  trigger(T01);
}
void pt2() {
  trigger(T00);
  trigger(T01);
  trigger(T00);
  trigger(T01);
  trigger(T01);

}

void pt3() {
  trigger(T02);
  trigger(T03);
  trigger(T02);
  trigger(T03);
  trigger(T00);
  trigger(T03);
}

void pt4() {
  delay(tempo);
  trigger(T07);
  trigger(T05);
  trigger(T00);
  delay(tempo);
  trigger(T00);
  trigger(T01);
  trigger(T08);
}

void pt5() {
  trigger(T09);
  trigger(T00);
  trigger(T00);
  trigger(T01);
  trigger(T04);
  trigger(T01);
  trigger(T09);
  trigger(T00);
}

void pt6() {
  trigger(T06);
  trigger(T05);
  trigger(T00);
  trigger(T03);
  trigger(T02);
  trigger(T09);
  trigger(T08);
  trigger(T01);
}


void pt7() {
  trigger(T05);
  delay(tempo);
  trigger(T09);
  trigger(T08);
  trigger(T03);
  trigger(T10);
  trigger(T06);
  trigger(T06);
}


void pt8() {
  trigger(T05);
  trigger(T09);
  trigger(T03);
  trigger(T09);
  delay(tempo);
  trigger(T03);
  trigger(T07);
  delay(tempo);
}


void pt9() {
  trigger(T01);
  trigger(T07);
  trigger(T08);
  trigger(T04);
  trigger(T09);
  delay(tempo);
  trigger(T02);
  trigger(T06);
}


void pt10() {
  trigger(T05);
  trigger(T01);
  trigger(T00);
  trigger(T05);
  trigger(T07);
  trigger(T08);
  trigger(T04);
  trigger(T07);
}

void pt11() {
  delay(tempo);
  trigger(T04);
  trigger(T03);
  trigger(T07);
  trigger(T04);
}



void pt12() {
  delay(tempo);
  trigger(T02);
  trigger(T08);
  trigger(T09);
  trigger(T10);
}



void pt13() {
  trigger(T04);
  trigger(T08);
  trigger(T03);
  trigger(T04);
  trigger(T00);
}



void pt14() {
  trigger(T01);
  delay(tempo);
  trigger(T04);
  trigger(T00);
  trigger(T09);
}



void pt15() {
  delay(tempo);
  trigger(T00);
  trigger(T04);
  trigger(T01);
  trigger(T08);
}



void pt16() {
  trigger(T06);
  trigger(T04);
  trigger(T02);
  trigger(T01);
  trigger(T08);
}



void pt17() {
  trigger(T08);
  delay(tempo);
  trigger(T09);
  trigger(T09);
  trigger(T00);
}



void pt18() {
  trigger(T00);
  trigger(T07);
  trigger(T03);
  trigger(T01);
  trigger(T06);
}



void pt19() {
  trigger(T09);
  trigger(T06);
  trigger(T03);
  trigger(T06);
  trigger(T07);
}



void pt20() {
  trigger(T07);
  trigger(T00);
  trigger(T07);
  trigger(T05);
  delay(tempo);
}


void pt21() {
  trigger(T00);
  delay(tempo);
  trigger(T00);
  delay(tempo);
  trigger(T00);
  delay(tempo);
  trigger(T00);
  delay(tempo);
}


