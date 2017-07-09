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
    float* fitnes;
    int n; //numero de entradas

    //creates a population of chromosomes
    population(int ind) {
      n = ind;
      chromosome = new byte[n];
      fitnes = new float[n];
    }

    //randomize the initial population
    randomize(){
     for (int i = 0; i < n; i++) {
        chromosome[i]= random(255);
      }

    }

    //function to read a particular gene of chromosome 0
    byte readGene(int pos){
      return bitRead(chromosome[0],pos);

    }

     //function to read a particular gene of chromosome ind
    byte readGene(int ind, int pos){
      return bitRead(chromosome[ind],pos);

    }

    //counts the number of bits ON of chromosome a
    int countBits(int a){
      byte count=0;
      for (int i = 0; i < 8; i++)
      {
        count+=bitRead(chromosome[a],i);
      }
      return count;
    }

    //** Replicaciton, mutation and crossover functions

    //copy chromosome 0
    copyIndividuals(){
     for (int i = 1; i < n; i++) {
        chromosome[i]= chromosome[0];
      }

    }

    mutateIndividuals(float p){
      int prop = int(p * 10000);//to use random as rulete
      for (int i = 1; i < n; i++) {
        for (int j = 0; j < 7; j++)
        {
          if(random(10000)<prop)
            //changes bit
            bitWrite(chromosome[i],j,!bitRead(chromosome[i],j));
        }
      }      

    }  


    crossover(int a, int b){
       byte cutPos=random(7);
       
       byte indA=chromosome[a];
       for (int i = 0; i <cutPos; i++)
       {
         bitWrite(chromosome[a],i,bitRead(chromosome[b],i));
         bitWrite(chromosome[b],i,bitRead(indA,i));
       }

    }  

    //Crossover of best with rest of population
    crossover(){
      for (int i = 0; i <n; i++){
         if(random(1)){
           crossover(0,i);
         }
      }

    } 



  private:
    //activation function


};
