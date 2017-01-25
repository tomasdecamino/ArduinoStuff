#define N 14
int aPin[N] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13};

void setup(){
  for(int i=0;i<N;i++){
    pinMode(aPin[i],INPUT);
  } 
  Serial.begin(9600);
}

void loop(){
  for(int i=0;i<N;i++){
    Serial.print(analogRead(aPin[i]));
    if(i<N-1)Serial.print(",");
  }
  Serial.println("");
  //delay(50);
}

