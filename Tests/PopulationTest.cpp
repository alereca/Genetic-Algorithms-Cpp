//
// Created by ale on 4/9/19.
//
#include "../single_include/catch2/catch.hpp"
#include "../Headers/Population.h"

SCENARIO("Population can execute its methods correctly", "[Population]") {
    GIVEN("Population initializes correctly"){
        double coefficientObjectiveFunction = 1;

        int numCromsInitial = 4;
        int numBinDigits = 5;
        int crossoverPosibility = 95;
        int mutationPosibility = 2;

        Chromosome::setCoefObjFunc(coefficientObjectiveFunction);

        Population pob(numCromsInitial, numBinDigits, crossoverPosibility, mutationPosibility);

        WHEN("")
    }
}
