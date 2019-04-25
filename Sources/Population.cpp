//
// Created by ale on 3/27/19.
//

#include <iostream>
#include "../Headers/Population.h"
#include "../Headers/RandomNumberGenerator.h"


template <typename Gen_Iterator> // This works for any type of iterator,
void Population::showCustom(Gen_Iterator start, Gen_Iterator end){ // however the behaviour changes depending on the parameters sent
    while(start != end){
        std::cout<< *start <<std::endl;
        start++;
    }
}


template <typename Gen_Iterator, typename Gen_Iterator2>
void Population::copyCustom(Gen_Iterator startContainer1, Gen_Iterator endContainer1, Gen_Iterator2 startContainer2, Gen_Iterator2 endContainer2){
    while(startContainer1 != endContainer1){
        *startContainer1 = *startContainer2;

        startContainer1++;
        startContainer2++;
    }
}


void Population::addCrom(Chromosome& crom){
    population_.push_back(crom);
}


void Population::setTotalAdaptToObjective() {
    this->totalAdaptationToObjective_ = 0;

    for (auto &crom : this->population_) {
        crom.setObjectivePunctuation();
        this->totalAdaptationToObjective_ += crom.getObjectivePunctuation();
    }
}


void Population::calculateCromsFitness() {
    for (auto &crom : this->population_) {
        crom.setFitness(this->totalAdaptationToObjective_);
    }
}


void Population::showCurrentPopulation() {
    for (auto &crom : this->population_) {
        crom.showData();
    }

    std::cout<<std::endl;
    std::cout<<"Min Objective Punctuation "<<this->minAdaptationToObjective_<<"\n";
    std::cout<<"Average Objective Punctuation "<<this->averageAdaptationToObjective_<<"\n";
    std::cout<<"Max Objective Punctuation "<<this->maxAdaptationToObjective_<<"\n";
}


void Population::reproduce(){
    std::vector<int> positionsSelectedCroms = this->selection();

    //Show all the selected croms
    /*std::cout<<std::endl;
    this->showCustom(positionsSelectedCroms.begin(), positionsSelectedCroms.end());*/

    this->crossOver(positionsSelectedCroms);

    this->setTotalAdaptToObjective();
    this->setStatisticalData();
    this->calculateCromsFitness();
}


std::vector<int> Population::selection() {
    std::vector<int> selectionPool;

    std::vector<int> selectionRoulette = this->makeRoulette();
    long selectionRoulette_size = selectionRoulette.size();

    // Here I rotate the roulette getting some potential fathers
    for (int i = 0; i < this->population_.size(); i++) {
        int cromPos = selectionRoulette[RandomNumberGenerator::getRandomInteger(0, selectionRoulette_size)];

        // So for {1,2,3,1,..} only checks if the value is repeated when iterating over 2 (pos 1) and 6 (pos 3), since vectors start from 0
        if(i % 2 != 0){
            // While loop in c++ uses "short-circuit" technique, so it only evaluates the first part and predicts the boolean result
            while((i > 0) && (cromPos == selectionPool[i-1])){
                cromPos = selectionRoulette[RandomNumberGenerator::getRandomInteger(0, selectionRoulette_size)];
            }
        }

        selectionPool.push_back(cromPos);
    }

    return selectionPool;
}


/*std::vector<int> Population::selection() {
    std::vector<int> selectionPool;

    std::vector<double> selectionRoulette = this->makeRoulette();
    long selectionRoulette_size = selectionRoulette.size();

    //showCustom(selectionRoulette.begin(), selectionRoulette.end());

    // Here I rotate the roulette getting some potential fathers
    *//*for (int i = 0; i < this->population_.size(); i++) {
        int cromPos = selectionRoulette[RandomNumberGenerator::getRandomInteger(0, selectionRoulette_size)];

        // So for {1,2,3,1,..} only checks if the value is repeated when iterating over 2 (pos 1) and 6 (pos 3), since vectors start from 0
        if(i % 2 != 0){
            // While loop in c++ uses "short-circuit" technique, so it only evaluates the first part and predicts the boolean result
            while((i > 0) && (cromPos == selectionPool[i-1])){
                cromPos = selectionRoulette[RandomNumberGenerator::getRandomInteger(0, selectionRoulette_size)];
            }
        }

        selectionPool.push_back(cromPos);
    }*//*
    for (int i = 0; i < this->population_.size(); i++) {
        int cromPos = selectOne(selectionRoulette, RandomNumberGenerator::getRandomReal(0, 100));

        if((i % 2) != 0){
            // While loop in c++ uses "short-circuit" technique, so it only evaluates the first part and predicts the boolean result
            while((i > 0) && (cromPos == selectionPool[i-1])){
                cromPos = selectOne(selectionRoulette, RandomNumberGenerator::getRandomReal(0, 100));
            }
        }

        selectionPool.push_back(cromPos);
    }


    return selectionPool;
}*/


int Population::selectOne(std::vector<double> selectionRoulette, double randomNum) {
    for (int j = selectionRoulette.size() - 1; j >= 0; j--) {
        if(selectionRoulette[j] < randomNum){
            return  j;
        }
    }

    return 0; // The element with the lowest accumulated fitness
}


std::vector<int> Population::makeRoulette() {
    std::vector<int> roulette;

    for (int i = 0; i < this->population_.size(); i++) {
        for (int j = i; j < ceil(this->population_[i].getFitness() * 100); j++) {
            roulette.push_back(i);
        }
    }

    return roulette;
}


/*std::vector<double> Population::makeRoulette() {
    std::vector<double> roulette;
    double fitnessAcum = 0; 
    
    for (auto &crom : this->population_) {
        fitnessAcum += crom.getFitness();
        roulette.push_back(fitnessAcum);
    }

    return roulette;
}*/


void Population::crossOver(std::vector<int> posSelectedCroms) {
    std::vector<Chromosome> selectedCromsToTransfer;

    for (int i = 0; i < posSelectedCroms.size() - 1; i += 2) {

        // Show selected pairs of croms
        std::cout<<std::endl;
        std::cout<<posSelectedCroms[i]<<"\n";
        std::cout<<posSelectedCroms[i+1]<<"\n";

        this->cross(this->population_[posSelectedCroms[i]], this->population_[posSelectedCroms[i+1]], selectedCromsToTransfer);
    }

    this->copyCustom(this->population_.begin(), this->population_.end(), selectedCromsToTransfer.begin(), selectedCromsToTransfer.end());
}


void Population::cross(Chromosome first_parent, Chromosome second_parent, std::vector<Chromosome>& selectedCromsToTransf) {

    int cromSize = first_parent.getSize();
    int crossingPoint = RandomNumberGenerator::getRandomInteger(1, cromSize - 1);

    //Show the crossing point selected
    /*std::cout<<std::endl;
    std::cout<<"Crossing Point: "<<crossingPoint<<"\n";*/

    Chromosome first_child(cromSize);
    Chromosome second_child(cromSize);

    if((RandomNumberGenerator::getRandomInteger(0, 100)) <= this->crossoverPossibility_){
        first_child.copy(first_parent, 0, crossingPoint);
        second_child.copy(second_parent, 0, crossingPoint);

        first_child.copy(second_parent, crossingPoint, cromSize);
        second_child.copy(first_parent, crossingPoint, cromSize);

        this->mutation(first_child);
        this->mutation(second_child);
    }
    else{
        first_child.copy(first_parent, 0, cromSize);
        second_child.copy(first_parent, 0, cromSize);
    }

    //Show first and second children
    /*std::cout<<std::endl;
    std::cout<<first_child.get_str()<<"\n";
    std::cout<<second_child.get_str()<<"\n";*/

    selectedCromsToTransf.push_back(first_child);
    selectedCromsToTransf.push_back(second_child);
}


// Wrapper for mutate method of a cromosoma
void Population::mutation(Chromosome& crom) {
    if((RandomNumberGenerator::getRandomInteger(0, 100)) <= this->mutationPossibility_){
        crom.mutate();
    }
}


void Population::setStatisticalData() {
    double maxObjPunc = 0;
    double minObjPunc = this->population_[0].getObjectivePunctuation();

    for (auto &crom : this->population_) {
        double cromObjPunctaution = crom.getObjectivePunctuation();

        if(cromObjPunctaution > maxObjPunc){
            maxObjPunc = cromObjPunctaution;
        }

        if(cromObjPunctaution < minObjPunc){
            minObjPunc = cromObjPunctaution;
        }
    }

    this->averageAdaptationToObjective_ = this->totalAdaptationToObjective_ / this->population_.size();
    this->maxAdaptationToObjective_ = maxObjPunc;
    this->minAdaptationToObjective_ = minObjPunc;
}


std::vector<double> Population::getStatisticalData() {
    std::vector<double> statisticalDataVec;

    statisticalDataVec.push_back(this->minAdaptationToObjective_);
    statisticalDataVec.push_back(this->averageAdaptationToObjective_);
    statisticalDataVec.push_back(this->maxAdaptationToObjective_);

    return statisticalDataVec;

}


/*bool Population::hasConverged() {
    int equalsCounter = 0;
    int population_size = this->population_.size();

    // Implement this in an efficient way

    std::cout<<equalsCounter<<" "<<ceil(population_size * 0.75)<<"\n";

    return equalsCounter > ceil(population_size * 0.75);
}*/










