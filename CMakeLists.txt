cmake_minimum_required(VERSION 3.13)
project(AlgoritmosGeneticosC__)

set(CMAKE_CXX_STANDARD 17)

# NO-UNIT-TESTS CONFIG
add_executable(AlgoritmosGeneticosC__ Sources/main.cpp Sources/Chromosome.cpp Headers/Chromosome.h Sources/Population.cpp Headers/Population.h Sources/generationsEvolution.cpp Headers/RandomNumberGenerator.h Sources/RandomNumberGenerator.cpp)

# ONLY-UNIT-TESTS CONFIG ( own main is not build)
#add_executable(AlgoritmosGeneticosC__ InitializeCatch.cpp ChromosomeTest.cpp Chromosome.cpp Chromosome.h Population.cpp Population.h PopulationTest.cpp)