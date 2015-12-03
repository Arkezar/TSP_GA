#include "genetic.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>

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
		candidate.setFitness( candidate.getTotalDistance() / sumOfDistances );
	}
}

void GA::SortCandidates(){
	std::sort(population.rbegin(), population.rend());
}

void GA::SelectCandidates(){

}

void GA::Execute(){
	SortCandidates();
	SelectCandidates();
}
