#ifndef GA_H
#define GA_H
#include <vector>
#include <unordered_map>
#include "data.h"
#include "dataloader.h"
// INIT - create random candidate solutions X
// EVALUATE each candidate
// WHILE( I < GENERATION NUMBER  )
//	SELECT PARENTS
//	RECOMBINE PAIRS OF PARENTS
//	MUTATE OFFSPRING
//	EVALUATE NEW CANDIDATES
//	SELECT CANDIDATES FOR NEXT GENERATION
std::vector<City> generateRandomCandidate(std::vector<City> cities);
double candidateEvaluation(const std::vector<City>& candidate, const std::unordered_map< std::pair<City, City>, double, pairhash>& distances);

class Candidate{
	private:
		std::vector<City> candidate;
		double totalDistance;
		double normalizedFitnessValue; // [0..1]
	public:
		Candidate(std::vector<City> candidate, const std::unordered_map< std::pair<City, City>, double, pairhash>& distances):candidate(candidate){
			totalDistance = candidateEvaluation(candidate, distances);
		}

		double getTotalDistance() const{
			return totalDistance;
		}
		void setFitness(double fitness){
			normalizedFitnessValue = fitness;
		}
		double getFitness() const{
			return normalizedFitnessValue;
		}
		std::vector<City> getCandidate() const{
			return candidate;
		}
};

inline std::ostream& operator<<(std::ostream& out, const Candidate& c){
			out << "Total Distance: " << c.getTotalDistance() << " Fitness: " << c.getFitness();	
			return out;
		}
static bool operator<(const Candidate& lhs, const Candidate& rhs){
	return lhs.getFitness() < rhs.getFitness();
};

class GA{
	private:
		int populationSize;
		int populationBreadersPercentage;
		int targetGenerationNumber;
		std::unordered_map< std::pair<City, City>, double, pairhash> distances;
		std::vector<City> baseCityVector; //probably I don't need this
		std::vector<Candidate> population;

		std::vector<Candidate> newPopulation;

		void Initialize(std::string filePath);
		void NormalizeCandidates();
	
		void SortCandidates();
		void SelectCandidates();
	public:
		GA(std::string filePath, int populationSize, int breedersPercentage, int targetGeneration)
			:populationSize(populationSize),populationBreadersPercentage(breedersPercentage){
			Initialize(filePath);
			NormalizeCandidates();
		}
		
		std::unordered_map< std::pair<City, City>, double, pairhash> getDistances(){
			return distances;
		}
		
		std::vector< Candidate > getPopulation(){
			return population;
		}

		void Execute();
};

#endif
