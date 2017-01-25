#include <Waveforms.h>

int i = 0;
int sample;

void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

// int val = map(analogRead(A0),0,1023,0,10000);
// int val2 =val+ map(analogRead(A1),0,1023,0,10000);

  sample = map(analogRead(A0), 0, 1023, 0, 10000);
 analogWrite(9, waveformsTable[0][i]);

  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;

  delayMicroseconds(sample);

// digitalWrite(9,HIGH);
// delayMicroseconds(val);
//  digitalWrite(9,LOW);
// delayMicroseconds(val2);
}
