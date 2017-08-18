//Tomas de Camino Beck
//Polymathboxes

#include <Wire.h>
#include "Chromosome.h"
#include <Adafruit_MCP4725.h>

#define N 10
#define POT1 A0
#define POT2 A3
#define POT3 A1
#define MIC1 A2
#define D 200


Adafruit_MCP4725 dac;

population pop(N);

float x = 0;
int val, val2;
float prob=0.05;
long loud = 0;

long lastMillis = millis();


void setup(void) {
  Serial.begin(9600);
  dac.begin(0x62);

  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
  pinMode(MIC1, INPUT);
}

void loop(void) {
  loud = 0;
  prob=(float)analogRead(POT3)/1023;
  val2 = map(analogRead(POT1), 0, 1023, 1, 16000);
  val = analogRead(POT2);
  // Push out the right lookup table, depending on the selected resolution
  pop.copyCrossover(2);
  pop.mutateChromosomes(prob, 1);
  evaluate();
  pop.sort();
  play(pop.chromosome[0], val*2);  
}

void play(int pitch, int tempo) {
  loud = 0;
  for (int i = 0; i < tempo; i++) {
    int w = round((2047 * sin(TWO_PI * x) + 2047));
    dac.setVoltage(w, false);
    //Serial.println(w);
    x += pitch;
    delayMicroseconds(val2);
    loud += analogRead(MIC1);
  }
}


void fitness(int a) {
  pop.fitness[a] = loud / 7500;
}

//Evalua cada cromosoma
void evaluate() {
  for (int i = 0; i < pop.n; i++) {
    play(pop.chromosome[i], D);
    fitness(i);
  }
}
