#include <iostream>
#include <vector>
#include <random>

enum Program_Spefications{
    NUM_CROMS_INITIAL = 10,
    NUM_BIN_DIGITS = 30,
    CROSSOVER_POSSIBILITY = 75,
    MUTATION_POSSIBILITY = 5,
    ITERATIONS_LIMIT = 20
    };

void generationsEvolution(std::vector<std::vector<double>>&, int, int, int, int, int);

int main(){
    std::vector<std::vector<double>> pobStatisticalData;

    generationsEvolution(
            pobStatisticalData,
            NUM_CROMS_INITIAL,
            NUM_BIN_DIGITS,
            CROSSOVER_POSSIBILITY,
            MUTATION_POSSIBILITY,
            ITERATIONS_LIMIT
            );


    /*std::cout<<std::endl;
    for (int i = 0; i < pobStatisticalData.size(); ++i) {
        for (int j = 0; j < pobStatisticalData[i].size(); ++j) {
            std::cout<<pobStatisticalData[i][j]<<" ";
        }
        std::cout<<"\n";
    }*/

    return 0;
}