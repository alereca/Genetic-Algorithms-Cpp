//
// Created by ale on 4/7/19.
//
#include "../single_include/catch2/catch.hpp"
#include <iostream>
#include "../Headers/Chromosome.h"


SCENARIO("Chromosome can execute its methods correctly", "[Chromosome]"){
    srand(time(0));

    GIVEN("Chromosome initializes correctly"){
        Chromosome::setCoefObjFunc(1);
        Chromosome crom(5);

        WHEN("The length is the one set in the constructor"){
            THEN("It should return that size"){
                REQUIRE(crom.getSize() == 5);
            }
        }

        WHEN("Objective adaptation is set in the constructor"){
            double ObjPunctuation = crom.getObjectivePunctuation();
            
            THEN("It should be a real number bigger than 0"){
                REQUIRE(static_cast<std::string>(typeid(ObjPunctuation).name()) == static_cast<std::string>("d"));
                REQUIRE(ObjPunctuation > 0.0);
            }
        }

        WHEN("Fitness is set in the constructor"){
            double fitness = crom.getFitness();

            THEN("It should be a real number equal to 0"){
                REQUIRE(static_cast<std::string>(typeid(fitness).name()) == static_cast<std::string>("d"));
                REQUIRE(fitness == 0.0);
            }
        }

        WHEN("Fitness is set when all chromosomes of the population are initialized"){
            double genericGlobalObjPunctuation = 10000 ;
            crom.setFitness(genericGlobalObjPunctuation);
            double fitness = crom.getFitness();

            THEN("It should be a real number between 0 and 100"){
                REQUIRE(static_cast<std::string>(typeid(fitness).name()) == static_cast<std::string>("d"));
                REQUIRE(fitness >= 0.0);
                REQUIRE(fitness <= 100.0);
            }
        }

        WHEN("The chromosome is copied with another chromsome content from a start to an end point"){
            Chromosome another_crom(5);
            int starting_point = 0;
            int end_point =  crom.getSize() / 2;

            crom.copy(another_crom, starting_point, end_point);

            THEN("The content should be the same as another_crom from the start to the end point given"){
                REQUIRE(crom.isEqual(another_crom, starting_point, end_point));
            }
        }

        WHEN("A Chromosome is mutated at some random position"){
            Chromosome originalCrom = crom;
            crom.mutate();

            THEN("It should be different from the original version"){
                REQUIRE(!(crom.isEqual(originalCrom, 0, crom.getSize())));
            }
        }

        WHEN("The method get_str is called in order to get the string representation of that Chromosome "){
            std::string crom_str = crom.get_str();

            THEN("The string should be equally sized to the Chromosome"){
                REQUIRE(crom.getSize() == crom_str.size());
            }
        }
    }
}
