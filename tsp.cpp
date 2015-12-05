#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <catch.hpp>
#include "genetic.h"

int main(int argc, char *argv[]){	
	std::srand(std::time(0));
	/*
	int populationSize = std::stoi(argv[1]);
	int breederPercentage = std::stoi(argv[2]);
	int targetGeneration = std::stoi(argv[3]);
	int mutationPercentage = std::stoi(argv[4]);

	std::cout << "Settings:\nPopulation:" << populationSize << "\nBreed %:" << breederPercentage << "\nTarget generation:" << targetGeneration << "\nMutation %:" << mutationPercentage << "\n";
	*/
	//int result = Catch::Session().run( argc, argv );
	//GA gaInst("att48.tsp",populationSize, breederPercentage, targetGeneration, mutationPercentage);
	GA gaInst("att48.tsp",10000, 10, 1000, 15);
	
	gaInst.Execute();
	return 0;
}
