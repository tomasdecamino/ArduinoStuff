//Tomas de Camino Beck
//www.funcostarica.org

#include "Chromosome.h"
#include <Adafruit_CircuitPlayground.h>

#define N 10

int luzActual, luzAnterior;

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
  pop.fitness[a] = 0.7 * float(CircuitPlayground.lightSensor()) - 0.3 * float(pop.countBits(a));
}

//Evalua cada cromosoma para ver cual es mejor
//y fija el cromosoma 0 a ese estado
void evaluate() {
  for (int i = 0; i < pop.n; i++) {
    setPixels(i);
    fitness(i);
    delay(10);
  }
}


void setup() {
  randomSeed(analogRead(A9));
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
  luzActual = CircuitPlayground.lightSensor();
}

void loop() {
  //Copia el cromosoma 0 a toda la población
  pop.copyChromosomes();

  //genera mutaciones en cada gen con
  //probabilidad 0.1
  pop.mutateChromosomes(0.1);

  //aplica recombinación con cromosoma 0
  pop.crossover(0.5);

  //reevalua fitnes el cromosoma 0 si hay cambios
  //importantes en la cantidad de luz
  //pues pueden haber cambios en el entorno
  //evalua
  evaluate();
  pop.sort();

  for (int i = 0; i < pop.n; i++) {
    Serial.println(pop.fitness[i]);
  }

  setPixels(0);

  //imprime a serial para ver los cambios
  Serial.println("_________");
  Serial.print(pop.chromosome[0]);
  Serial.print(",");
  Serial.print(pop.countBits(0));
  Serial.print("|");
  Serial.println(pop.fitness[0]);
  Serial.println("_________");

  //espera segundo y medio
  delay(1500);
}
