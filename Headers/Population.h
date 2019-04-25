//
// Created by ale on 3/27/19.
//

#ifndef ALGORITMOSGENETICOSC___POPULATION_H
#define ALGORITMOSGENETICOSC___POPULATION_H

#include <vector>
#include "Chromosome.h"

class Population {
private:
    std::vector<Chromosome> population_;
    int crossoverPossibility_;
    int mutationPossibility_;
    double totalAdaptationToObjective_{};
    double averageAdaptationToObjective_{};
    double maxAdaptationToObjective_{};
    double minAdaptationToObjective_{};

    // This classes directly access this auxiliary method for another functions
    std::vector<int> selection();
    int selectOne(std::vector<double>, double);
    std::vector<int> makeRoulette();
    void crossOver(std::vector<int>);
    void cross(Chromosome, Chromosome, std::vector<Chromosome>&);
    void mutation(Chromosome&);
    void setTotalAdaptToObjective();
    void setStatisticalData();
    void calculateCromsFitness();

    template <typename Gen_Iterator>
    void showCustom(Gen_Iterator, Gen_Iterator);

    template <typename Gen_Iterator, typename Gen_Iterator2>
    void copyCustom(Gen_Iterator, Gen_Iterator, Gen_Iterator2, Gen_Iterator2);

public:
    // Try to use an even number to set the initial population
    Population(size_t N_Croms, int N_bin_digits, int crossoverPosib, int mutationPosib) {
        for (int i = 0; i < N_Croms; ++i) {
            Chromosome generic_crom(N_bin_digits);

            this->addCrom(generic_crom);
        }

        this->setTotalAdaptToObjective();
        this->setStatisticalData();
        this->calculateCromsFitness();

        this->crossoverPossibility_ = crossoverPosib;
        this->mutationPossibility_ = mutationPosib;
    }

    ~Population() = default;

    void addCrom(Chromosome&);
    void showCurrentPopulation();
    std::vector<double> getStatisticalData();
    void reproduce();
    //bool hasConverged();
};


#endif //ALGORITMOSGENETICOSC___POPULATION_H
