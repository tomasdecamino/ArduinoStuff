//Tomas de Camino Beck

#include "Chromosome.h"
#include <Adafruit_CircuitPlayground.h>

#define N 10

//crea la poblacion
population pop(N);

//prende los pixles dependiendo de los bits en el cromosoma
void setPixels(int a) {
  for (int i = 0; i < 8; i++) {
    if (bitRead(pop.chromosome[a], i)) {
      CircuitPlayground.setPixelColor(i + 2, CircuitPlayground.strip.Color(255, 255, 255));
    } else {
      CircuitPlayground.setPixelColor(i + 2, CircuitPlayground.strip.Color(0, 0, 0));
    }
  }
}

//Calcula el fitnes basado en la cantidad de luz (maximiza)
//y la cantidad de leds (minimiza)
void fitness(int a) {
  pop.fitnes[a] = 0.7 * float(CircuitPlayground.lightSensor()) - 0.3 * float(pop.countBits(a));
  Serial.print(pop.countBits(a));
}

//Evalua cada cromosoma para ver cual es mejor
//y fija el cromosoma 0 a ese estado
void evaluate() {
  for (int i = 1; i < pop.n; i++) {
    setPixels(i);
    fitness(i);
    Serial.print(",");
    Serial.println(pop.fitnes[i]);
    if (pop.fitnes[0] < pop.fitnes[i]) {
      pop.chromosome[0] = pop.chromosome[i];
      pop.fitnes[0] = pop.fitnes[i];
    }
    delay(10);
  }
}


void setup() {
  randomSeed(analogRead(A9));
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
  //pop.randomize();
  //pop.chromosome[0] = 0;
  pop.fitnes[0] = 0;
}

void loop() {
  //Copia el cromosoma 0 a toda la población
  pop.copyIndividuals();
  //genera mutaciones en cada gen con 
  //probabilidad 0.1
  pop.mutateIndividuals(0.1);
  //aplica recombinación con cromosoma 0
  pop.crossover();
  //reevalua fitnes el cromosoma 0
  //pues pueden haber cambios en el entorno
  fitness(0);
  //evalua
  evaluate();
  setPixels(0);

  //imprime a serial para ver los cambios
  Serial.println("_________");
  Serial.print(pop.chromosome[0]);
  Serial.print(",");
  Serial.print(pop.countBits(0));
  Serial.print("|");
  Serial.println(pop.fitnes[0]);
  Serial.println("_________");

  //espera segundo y medio
  delay(1500);
}
