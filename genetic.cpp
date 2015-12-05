#include "genetic.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>

std::vector<City> generateRandomCandidate(std::vector<City> cities){

	std::vector<City> resultingCandidate;
	while(cities.size() > 0){
		auto tmp = cities.at( std::rand() % cities.size() ); 
		resultingCandidate.push_back(tmp);
		cities.erase( std::find( cities.begin(), cities.end()-1, tmp ) );
	}
	return resultingCandidate;
}

double candidateEvaluation(const std::vector<City>& candidate, const std::unordered_map< std::pair<City, City>, double, pairhash>& distances){
	double totalDistance = 0;
	for(int i=0; i < candidate.size() - 1; i++){
		auto pair = std::make_pair(candidate.at(i),candidate.at(i+1));
		totalDistance += distances.at(pair);
	}
	return totalDistance;
}

void GA::Initialize(std::string filePath){
	std::string fpath(filePath);
	baseCityVector = loadDataFromFile(fpath);
	distances = createDistanceMatrix(baseCityVector);
	for(int i = 0; i < populationSize ; i++){
		population.push_back( Candidate(generateRandomCandidate(baseCityVector),distances) );
	}
}

void GA::NormalizeCandidates(){
	double sumOfDistances =0;
	for(const auto& candidate : population){
		sumOfDistances += candidate.getTotalDistance();
	}
	for(auto& candidate : population){
		candidate.setFitness(1 - (candidate.getTotalDistance() / sumOfDistances ));
	}
}

void GA::SortCandidates(){
	std::sort(population.rbegin(), population.rend());
}

void GA::SelectParents(int populationPercentage){
	int parentPopulationSize = populationSize * populationPercentage / 100;
	std::vector<Candidate> tournament;
	while(parentsPopulation.size() < parentPopulationSize){
		tournament.clear();
		for(int i = 0; i < std::sqrt(parentPopulationSize); i++){
			tournament.push_back(population.at(std::rand() % populationSize));
		}
		std::sort(tournament.rbegin(), tournament.rend());
		parentsPopulation.push_back( tournament.at(0) );
		parentsPopulation.push_back( tournament.at(1) );
	}
}

void GA::CycleCrossover(Candidate p1, Candidate p2){
	int startingGene = std::rand() % p1.getCandidate().size();
	int currentGene = -1;
	std::vector<City> child1(p1.getCandidate());
	std::vector<City> child2(p2.getCandidate());
		
	CycleCrossover_MixGenes(child1,child2,currentGene,startingGene);
	newPopulation.push_back(p1);
	newPopulation.push_back(p2);

	Candidate newChild1 = Candidate(child1,distances);
	Candidate newChild2 = Candidate(child2,distances);
	if(!newChild1.isUnique() || !newChild2.isUnique())
		throw new std::logic_error("Invalid child sequence");

	newPopulation.push_back(newChild1);
	newPopulation.push_back(newChild2);

	//std::cout << "P1 " << p1 << "\n";
	//std::cout << "P2 " << p2 << "\n";
	//std::cout << "C1 " << newChild1 << "\n";
	//std::cout << "C2 " << newChild2 << "\n";
	//if(newChild1.getFitness() > p1.getFitness())

}

void GA::CycleCrossover_MixGenes(std::vector<City>& p1, std::vector<City>& p2, int& currentGenePos, const int& startingGenePos){
	if(startingGenePos == currentGenePos){
		return;
	}else{
		if(currentGenePos == -1){
			currentGenePos = startingGenePos;
		}
		City currentGeneParent1(p1.at(currentGenePos));
		City currentGeneParent2(p2.at(currentGenePos));
		
		int nextGenePos = std::find(p1.begin(), p1.end(), currentGeneParent2) - p1.begin();
		if(nextGenePos == p1.size()){
			nextGenePos = startingGenePos;
		}
		p1[currentGenePos] = currentGeneParent2;
		p2[currentGenePos] = currentGeneParent1;
		currentGenePos = nextGenePos;

		CycleCrossover_MixGenes(p1,p2,currentGenePos,startingGenePos);
	}
}

void GA::Mutate(Candidate& candidate){
	int mutatedGenPos1 = std::rand() % candidate.getCandidate().size();	
	int mutatedGenPos2 = std::rand() % candidate.getCandidate().size();
	auto tmpGene = candidate.getCandidate()[mutatedGenPos2];
	candidate.getCandidate()[mutatedGenPos2] = candidate.getCandidate()[mutatedGenPos1];
	candidate.getCandidate()[mutatedGenPos1] = tmpGene;
}

void GA::Execute(){
	std::cout << "Solving TSP\n";
	for(int g = 1; g < targetGenerationNumber; g++){
		std::cout << "Current generation: " << g << "\n";
		SortCandidates();
		while(newPopulation.size() < populationSize){
//			std::cout << "New population size: " << newPopulation.size() << std::endl;
			parentsPopulation.clear();
			SelectParents(populationBreadersPercentage);
			for(int i = 0 ; i < parentsPopulation.size()-1; i+=2){
				CycleCrossover(parentsPopulation.at(i),parentsPopulation.at(i+1));
			}
		}
		for(int m = 0; m < newPopulation.size() * mutationPercentage / 100; m++){
			auto mutant = newPopulation[std::rand() % newPopulation.size()];
			Mutate(mutant);
			mutant.ReEvaluate(distances);
		}
		population = newPopulation;
		newPopulation.clear();
		NormalizeCandidates();
		SortCandidates();
		std::cout << "Best: " << population.at(0) << "\n";
	}
}
