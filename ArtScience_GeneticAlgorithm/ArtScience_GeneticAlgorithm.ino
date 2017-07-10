//Tomas de Camino Beck
//www.funcostarica.org

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
  pop.fitness[a] = 0.7 * float(CircuitPlayground.lightSensor()) - 0.3 * float(pop.countBits(a));
}

//Evalua cada cromosoma
void evaluate() {
  for (int i = 0; i < pop.n; i++) {
    setPixels(i);
    //gives LED time to turn on
    delay(30);
    fitness(i);
  }
}


void setup() {
  randomSeed(analogRead(A9));
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
  //inicia con una población aleatoria
  pop.mutateChromosomes(0.5,0);
}

void loop() {
 
  //aplica recombinación con cromosoma 0 a 2 y los copia en una población
  pop.copyCrossover(2);

  //genera mutaciones en cada gen con
  //probabilidad 0.1
  pop.mutateChromosomes(0.1, 1);

  //evalua
  evaluate();

  //Ordena los cromosomas de mayr a menor fitness
  pop.sort();

  //prende los leds que correspoden al mejor fitness
  setPixels(0);

  //espera segundo y medio
  delay(1500);
}

