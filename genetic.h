#ifndef GA_H
#define GA_H
#include <vector>
#include <unordered_map>
#include "data.h"
#include "dataloader.h"
// INIT - create random candidate solutions X
// EVALUATE each candidate X
// WHILE( I < GENERATION NUMBER  )
//	SELECT PARENTS X
//	RECOMBINE PAIRS OF PARENTS X
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
		std::vector<City>& getCandidate(){
			return candidate;
		}
		void ReEvaluate(const std::unordered_map< std::pair<City, City>, double, pairhash>& distances){
			totalDistance = candidateEvaluation(candidate,distances);
		}
		void PrintRoute(){
			std::cout << "Route:\n";
			for(int i = 0; i < candidate.size(); i++){
				std::cout << i << " => " << candidate.at(i) << "\n";
			}
		}
		bool isUnique(){
			int count;
			for(const auto& c : candidate){
				count = 0;
				for(const auto& city : candidate){
					if(city == c)
						count++;
				}
				if(count > 1)
					return false;
			}
			return true;
		}
};



inline std::ostream& operator<<(std::ostream& out, const Candidate& c){
			out << "Total Distance: " << c.getTotalDistance() << " Fitness: " << c.getFitness();	
			return out;
		}
static bool operator<(const Candidate& lhs, const Candidate& rhs){
	return lhs.getFitness() < rhs.getFitness();
};
/*static bool operator==(const Candidate& lhs, const Candidate& rhs){
	bool result = true;
	for(int i = 0; i < lhs.getCandidate().size(); i++){
		if(lhs.getCandidate().at(i) == lhs.getCandidate().at(i)){

		}
		else {
			result = false;
			break;
		}
	}
	return lhs.getFitness() < rhs.getFitness();
};*/


class GA{
	private:
		int populationSize;
		int populationBreadersPercentage;
		int mutationPercentage;
		int targetGenerationNumber;
		std::unordered_map< std::pair<City, City>, double, pairhash> distances;
		std::vector<City> baseCityVector; //probably I don't need this
		std::vector<Candidate> population;
		
		std::vector<Candidate> parentsPopulation;
		std::vector<Candidate> newPopulation;

		void Initialize(std::string filePath);
		void NormalizeCandidates();
		
		void SortCandidates();
		void SelectParents(int);
		void CycleCrossover(Candidate p1, Candidate p2);
		void CycleCrossover_MixGenes(std::vector<City>& p1, std::vector<City>& p2, int& currentGene, const int& startingGene);
		void Mutate(Candidate& c);
	public:
		GA(std::string filePath, int populationSize, int breedersPercentage, int targetGeneration, int muationPercenage)
			:populationSize(populationSize),populationBreadersPercentage(breedersPercentage), mutationPercentage(mutationPercentage),targetGenerationNumber(targetGeneration){
			Initialize(filePath);
			NormalizeCandidates();
		}
		
		std::unordered_map< std::pair<City, City>, double, pairhash> getDistances(){
			return distances;
		}
		
		std::vector< Candidate > getPopulation(){
			return population;
		}

		std::vector<Candidate> getParentPopulation(){
			return parentsPopulation;
		}

		void Execute();
};

#endif
