//
// Created by ale on 4/14/19.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "../Headers/Population.h"
#include "../Headers/Chromosome.h"


void generationsEvolution(
        std::vector<std::vector<double>>& pobStatisticalData,
        const int NUM_CROMS_INITIAL,
        const int NUM_BIN_DIGITS,
        const int CROSSOVER_POSSIBILITY,
        const int MUTATION_POSSIBILITY,
        const int ITERATIONS_LIMIT){

    // Class method to set global coefficient of all instances of Chromosome
   double coefficientObjectiveFunction = pow(2, 30) - 1;
   Chromosome::setCoefObjFunc(coefficientObjectiveFunction);


   Population pob(NUM_CROMS_INITIAL, NUM_BIN_DIGITS, CROSSOVER_POSSIBILITY, MUTATION_POSSIBILITY);
   int iterations = 0;


   do{
       std::cout<<"\n"<<"Generation number: "<<iterations<<"\n";

       pob.showCurrentPopulation();

       pobStatisticalData.push_back(pob.getStatisticalData());

       // In the last iteration the crom population doesn't reproduce
       if(iterations < ITERATIONS_LIMIT - 1){
           pob.reproduce();
       }

       iterations++;
   } while((iterations < ITERATIONS_LIMIT));
}
