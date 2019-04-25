//
// Created by ale on 4/24/19.
//
#include "../Headers/RandomNumberGenerator.h"


// https://stackoverflow.com/questions/8971824/multiple-definition-of-namespace-variable-c-compilation
namespace RandomNumberGenerator{
    std::random_device rd;
    std::mt19937 rg(rd());

    int getRandomInteger(int start, int end) {
        std::uniform_int_distribution<int> dis(start, end);

        auto random_integer = dis(rg);

        return random_integer;
    }

    double getRandomReal(double start, double end) {
        std::uniform_real_distribution<double> dis(start, end);

        auto random_real = dis(rg);

        return random_real;
    }
}
