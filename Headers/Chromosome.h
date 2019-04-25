//
// Created by ale on 3/27/19.
//

#ifndef ALGORITMOSGENETICOSC___CHROMOSOME_H
#define ALGORITMOSGENETICOSC___CHROMOSOME_H

#include <vector>
#include "RandomNumberGenerator.h"

class Chromosome {
private:
    std::vector<int> crom_;
    double fitness_;
    double adaptToObj_{};

    static double coefObjFunc_;

    // This classes directly access this auxiliary method for another functions
    static char binaryToChar(int binary_digit);

    double getRealValue();
    std::vector<int> getCromVector();

public:
    explicit Chromosome(int N_bin_digits){
        for (int i = 0; i < N_bin_digits; i++) {
            this->crom_.push_back(RandomNumberGenerator::getRandomInteger(0,1));
        }

        this->setObjectivePunctuation();
        this->fitness_ = 0;
    }

    ~Chromosome() = default;

    static void setCoefObjFunc(double);

    std::string get_str();
    void showData();
    int getSize();
    void setObjectivePunctuation();
    double getObjectivePunctuation();
    void setFitness(double);
    double getFitness();
    void copy(Chromosome, int, int);
    void mutate();
    bool isEqual(Chromosome, int, int);
};


#endif //ALGORITMOSGENETICOSC___CHROMOSOME_H
