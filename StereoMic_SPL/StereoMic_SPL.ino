#define TH 10
#define MAXL 500
#define MAXR 500



long sumL,sumR;
long lastMillis;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  digitalWrite(2,HIGH);  
  digitalWrite(4,HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lastMillis=millis();
  sumL=0;
  sumR=0;
  while(millis()-lastMillis<TH){
    int valL=abs(512-analogRead(A0));
    int valR=abs(512-analogRead(A1));
    if(valL>MAXL)sumL++;
    if(valR>MAXR)sumR++;
  }
  Serial.print(sumL);
  Serial.print(',');
  Serial.println(sumR);
}
