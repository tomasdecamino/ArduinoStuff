/*Tomas de Camino Beck

  Class Chromosome to use in a genetic algorithm
  It creates a population of chromosomes.  The class
  allows for crhomosome mutation and crossover operations.
  Fitness evaluation has to be programmed in the main code

  Best fit chromosome is assumed to be chromosome 0

  Ussage:
  1. create a objet class chromosome initialize population of n
  2. Create a fitness and evaluation functions (in main code)
  3. Choose best fit (in main code)
  3. use mutation and crossover over class crhomosome

  Made for teaching poruposes www.funcostarica.org
*/
//**************Class population*************
class population
{

  public:
    //
    byte* chromosome;
    float* fitness;
    int n; //numero de entradas

    //creates a population of chromosomes
    population(int ind) {
      n = ind;
      chromosome = new byte[n];
      fitness = new float[n];
    }

    //randomize the initial population
    randomize() {
      for (int i = 0; i < n; i++) {
        chromosome[i] = random(255);
      }

    }

    //uses bubble sort, sorting by fitnes
    void sort()
    {
      int i, j;
      for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
          if (fitness[j] < fitness[j + 1]) {
            //swap fitnes
            float f = fitness[j];
            fitness[j] = fitness[j + 1];
            fitness[j + 1] = f;
            //swap chromosome
            byte ind = chromosome[j];
            chromosome[j] = chromosome[j + 1];
            chromosome[j + 1] = ind;
          }
        }
      }
    }

    //function to read a particular gene of chromosome 0
    byte readGene(int pos) {
      return bitRead(chromosome[0], pos);

    }

    //function to read a particular gene of chromosome ind
    byte readGene(int ind, int pos) {
      return bitRead(chromosome[ind], pos);

    }

    //counts the number of bits ON of chromosome a
    int countBits(int a) {
      byte count = 0;
      for (int i = 0; i < 8; i++)
      {
        count += bitRead(chromosome[a], i);
      }
      return count;
    }

    //** Replicaciton, mutation and crossover functions

    //copy chromosome 0
    copyChromosomes() {
      for (int i = 1; i < n; i++) {
        chromosome[i] = chromosome[0];
      }

    }

    mutateChromosomes(float p) {
      int prop = int(p * 10000);//to use random as rulete
      for (int i = 1; i < n; i++) {
        for (int j = 0; j < 7; j++)
        {
          if (random(10000) < prop)
            //changes bit
            bitWrite(chromosome[i], j, !bitRead(chromosome[i], j));
        }
      }

    }

    //mutate chromosomes, starting from first
    mutateChromosomes(float p, int first) {
      int prop = int(p * 10000);//to use random as rulete
      for (int i = first; i < n; i++) {
        for (int j = 0; j < 7; j++)
        {
          if (random(10000) < prop)
            //changes bit
            bitWrite(chromosome[i], j, !bitRead(chromosome[i], j));
        }
      }

    }


    byte crossover(int a, int b) {
      byte cutPos1 = random(4);
      byte cutPos2 = random(4, 7);

      byte indA = chromosome[a];
      for (int i = cutPos1; i < cutPos2; i++)
      {
        bitWrite(indA, i, bitRead(chromosome[b], i));
      }
      return indA;
    }


    //crosover with 0 with some probability p
    copyCrossover(int m) {
      int r = 0;
      for (int i = m; i < n; i++) {
        int cA = random(m);
        int cB = random(m);
        chromosome[i] = crossover(cA, cB);
      }

    }



  private:
    //


};

