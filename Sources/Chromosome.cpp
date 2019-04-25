//
// Created by ale on 3/27/19.
//

#include <iostream>
#include <cmath>
#include "../Headers/Chromosome.h"
#include "../Headers/RandomNumberGenerator.h"


//Since it's a static member I have to define it again here, so the linker knows what this variable is
double Chromosome::coefObjFunc_ = 0;


// Private Auxiliary Function
char Chromosome::binaryToChar(int binary_digit) {
    if(binary_digit) return '1';
    else return '0';
}


// In order to convert a char to int, use intV = castToInt(charV) + 48
double Chromosome::getRealValue(){
    double realNum = 0;
    unsigned long crom_size = this->crom_.size();

    for (int i = 0, z = crom_size - 1; i < crom_size; i++, z--) {
        realNum += this->crom_[i] * (pow(2, z));
    }

    return realNum;
}


// Public Functions
std::string Chromosome::get_str() {
    std::string binary_str;

    for (const auto &bin_digit : this->crom_) {
        binary_str.push_back(binaryToChar(bin_digit));
    }

    return binary_str;
}


void Chromosome::showData() {
    std::cout<<this->get_str()<<" "<<this->getObjectivePunctuation()<<" "<<this->getFitness()<<"\n";
}


void Chromosome::setObjectivePunctuation(){

    this->adaptToObj_ = pow((this->getRealValue() / Chromosome::coefObjFunc_), 2) ;
}


double Chromosome::getObjectivePunctuation() {

    return this->adaptToObj_;
}


void Chromosome::setFitness(double globalObjectivePunctuation) {
    this->fitness_ = (this->adaptToObj_ / globalObjectivePunctuation) * 100;
}


double Chromosome::getFitness() {
    return fitness_;
}


int Chromosome::getSize() {
    return this->crom_.size();
}


void Chromosome::copy(Chromosome anotherCrom, int from, int end) {
    for (int i = from; i < end; i++) {
        this->crom_[i] = anotherCrom.crom_[i];
    }
}


void Chromosome::mutate() {
    int mutationPoint = RandomNumberGenerator::getRandomInteger(0, this->getSize() - 1);

    this->crom_[mutationPoint] = !(this->crom_[mutationPoint]);
}


void Chromosome::setCoefObjFunc(double sentCoef) {
    Chromosome::coefObjFunc_ = sentCoef;
}


bool Chromosome::isEqual(Chromosome anotherCrom, int start, int end) {
    auto anotherCromVector = anotherCrom.getCromVector();

    for (int i = start; i < end; i++) {
        if(this->crom_[i] != anotherCromVector[i]){
            return false;
        }
    }

    return true;
}


std::vector<int> Chromosome::getCromVector() {
    return this->crom_;
}






