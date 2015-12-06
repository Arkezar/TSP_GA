#include "genetic.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <stdexcept>
#include <future>
#include <thread>

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
	std::cout << "City vector size: " << baseCityVector.size() << "\n";
	for(const auto& c : baseCityVector)
		std::cout << c << "\n";

	distances = createDistanceMatrix(baseCityVector);
	for(int i = 0; i < populationSize ; i++){
		population.push_back( Candidate(generateRandomCandidate(baseCityVector),distances) );
	}
	maxXPosition = 0;
	maxYPosition = 0;
	for(const auto& city : population[0].getCandidate()){
		if(city.getX() > maxXPosition)
			maxXPosition = city.getX();
		if(city.getY() > maxYPosition)
			maxYPosition = city.getY();
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
	int parentsPopulationSize = (1 - (populationPercentage / 100.0)) * populationSize;
	//std::cout << "Parents popoulation size: " << parentsPopulationSize << "\n";
	parentsPopulation = std::vector<Candidate>(population.begin(), population.begin()+parentsPopulationSize);
	
	/*
	int parentPopulationSize = populationSize * populationPercentage / 100;
	std::vector<Candidate> tournament;
	while(parentsPopulation.size() < parentPopulationSize){
		tournament.clear();
		for(int i = 0; i < std::sqrt(parentPopulationSize); i++){
			tournament.push_back(population.at(std::rand() % populationSize));
		}
		std::sort(tournament.rbegin(), tournament.rend());
		for(int i = 0; i < 2; i++)
		if(std::find(parentsPopulation.begin(), parentsPopulation.end(), tournament.at(i))==parentsPopulation.end()){
			std::cout << "Parents population: " << parentsPopulation.size() << "\n";
			parentsPopulation.push_back( tournament.at(i) );
		}
		//parentsPopulation.push_back( tournament.at(1) );
	}
	*/
}

void GA::CycleCrossover(Candidate p1, Candidate p2){
	int startingGene = std::rand() % p1.getCandidate().size();
	int currentGene = -1;
	std::vector<City> child1(p1.getCandidate());
	std::vector<City> child2(p2.getCandidate());
		
	CycleCrossover_MixGenes(child1,child2,currentGene,startingGene);
	//newPopulation.push_back(p1);
	//newPopulation.push_back(p2);

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

Candidate GA::PMXCrossover(const Candidate& p1, const Candidate& p2){
//	std::cout << "Starting crossover\n";
	int startPos = std::rand() % p1.getCandidate().size();
	int endPos = -1;
	while(endPos == -1){
		int tmpPos = std::rand() % p1.getCandidate().size();
		if(tmpPos > startPos)
			endPos = tmpPos;
		else if(tmpPos < startPos){
			endPos = startPos;
			startPos = tmpPos;
		}
	}

//	std::cout << "swath start: " << startPos << "\nswath end: " << endPos << "\n";

	std::vector<City> child(p1.getCandidate().size());
	std::vector<bool> childCompletion(p1.getCandidate().size());
	//COPY RANDOM SWATH OF GENES
	//std::copy(p1.getCandidate().begin() + startPos, 
	//		p1.getCandidate().begin() + endPos, 
	//		child.begin() + startPos);
	//
	for(int i = startPos; i <= endPos; i++){
		child[i] = p1.getCandidate().at(i);
	}

	//for(const auto& c : child){
	//	std::cout << c << "\n";
	//}
	for(int i = startPos; i <= endPos; i++)
		childCompletion[i] = true;
	//FIND FIRST GENE IN PARENT 2 THAT WASN'T COPIED TO CHILD
	
	for(int i = startPos; i <= endPos; i++){
		auto tmpGene = std::find(child.begin(), child.end(), p2.getCandidate().at(i));
		if(tmpGene == child.end()){
			int destPosition = PMXCrossover_FindDestPosition(p1.getCandidate(),p2.getCandidate(),startPos,endPos,i);
//			std::cout << "Place " << p2.getCandidate().at(i) << " at pos " << destPosition << "\n";
			child[destPosition] = p2.getCandidate().at(i);
			childCompletion[destPosition] = true;
		}
	}

	for(int i = 0; i< child.size(); i++){
		if(!childCompletion[i])
			child[i] = p2.getCandidate().at(i);
	}

	Candidate result = Candidate(child, distances);
	if(!result.isUnique()){
		for(const auto& c : result.getCandidate())
			std::cout << c << "\n";
		throw new std::logic_error("Invalid child sequence");
	}	
	return result;
}

int GA::PMXCrossover_FindDestPosition(const std::vector<City>& p1cities, const std::vector<City>& p2cities, const int& startPos, const int& endPos, int currentPos){
	
	auto tmpGenePos = std::find(p2cities.begin(), p2cities.end(), p1cities.at(currentPos)) - p2cities.begin();
	if(tmpGenePos < startPos || tmpGenePos > endPos){
		return tmpGenePos;	
	}else{
		PMXCrossover_FindDestPosition(p1cities,p2cities,startPos,endPos,tmpGenePos);
	}

}

void GA::Mutate(Candidate& candidate, int mutationPower){
	for(int i = 0; i < mutationPower; i++){
		int mutatedGenPos1 = std::rand() % candidate.getCandidate().size();	
		int mutatedGenPos2 = std::rand() % candidate.getCandidate().size();
		auto tmpGene = candidate.getCandidate()[mutatedGenPos2];
		candidate.getCandidate()[mutatedGenPos2] = candidate.getCandidate()[mutatedGenPos1];
		candidate.getCandidate()[mutatedGenPos1] = tmpGene;
	}
}

void GA::Execute(){
	std::cout << "Solving TSP\n";
		SDL_Window *window = NULL;
	//SDL_Surface *surface;
	SDL_Init(SDL_INIT_VIDEO);
	const int wWidth = 640;
	const int wHeight = 480;
	window = SDL_CreateWindow("TSP Visualizer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wWidth,wHeight,SDL_WINDOW_OPENGL);
	//surface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	std::vector<SDL_Rect> cityDots;
	for(const auto& c : baseCityVector){
		SDL_Rect dot;
		dot.x = c.getX() * wWidth / maxXPosition - 2;
		dot.y = c.getY() * wHeight / maxYPosition - 2;
		dot.w = 4;
		dot.h = 4;
		cityDots.push_back(dot);
	}

	for(int g = 1; g < targetGenerationNumber; g++){
		currentGeneration = g;
		std::cout << "Current generation: " << g << "\n";
		SortCandidates();
		//std::cout << "Sorted population\n";
		parentsPopulation.clear();
		SelectParents(populationBreadersPercentage);
		int childrenPopulationSize = populationSize * populationBreadersPercentage / 100;	
		//std::cout << "Childrem population size: " << childrenPopulationSize << "\n";
		while(newPopulation.size() < childrenPopulationSize){
			//std::cout << "New pop size: " << newPopulation.size() << "\n";
			auto parent1 = parentsPopulation.at( std::rand() % parentsPopulation.size() );
			auto parent2 = parentsPopulation.at( std::rand() % parentsPopulation.size() );
			
			//std::future<Candidate> fChild1 = std::async(GA::PMXCrossover,parent1,parent2);
			
			Candidate child1 = PMXCrossover(parent1,parent2);
			Candidate child2 = PMXCrossover(parent2,parent1);
			//if(std::find(newPopulation.begin(),newPopulation.end(),child) == newPopulation.end())
			newPopulation.push_back ( child1 );
			newPopulation.push_back ( child2 );
		}
		//std::cout << "Created new population\n";
		for(int m = 1; m <= newPopulation.size() * mutationPercentage / 100; m++){
			//auto mutant = newPopulation[std::rand() % newPopulation.size()];
			auto mutant = newPopulation[ (std::rand() * m) % newPopulation.size()];
			Mutate(mutant, mutationPower);
			mutant.ReEvaluate(distances);
		}
		//std::cout << "Mutated population\n";
		population.insert(population.end(), newPopulation.begin(), newPopulation.end());
		newPopulation.clear();
		NormalizeCandidates();
		SortCandidates();
		population = std::vector<Candidate>(population.begin(),population.begin()+populationSize);
		std::cout << "Best: " << population.at(0) << "\n";
		
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderClear(renderer);
				
		std::vector<SDL_Point> cityPositions;
				/*
		int maxX;
		int maxY;
		for(const auto& city : getBest().getCandidate()){
			maxX = 0;
			maxY = 0;
			if(city.getX() > maxX)
				maxX = city.getX();
			if(city.getY() > maxY)
				maxY = city.getY();
		}	
		*/
		
		for(const auto& city : population[0].getCandidate()){
			int posY = city.getY() * wHeight / maxYPosition;
			int posX = city.getX() * wWidth / maxXPosition;

			SDL_Point position;
			position.y = city.getY() * wHeight / maxYPosition;
			position.x = city.getX() * wWidth / maxXPosition;
			cityPositions.push_back(position);

			
		}
		SDL_SetRenderDrawColor(renderer, 255,0,0,255);

		SDL_RenderDrawLines(renderer, &cityPositions[0], cityPositions.size());
		SDL_SetRenderDrawColor(renderer, 0,255,0,255);
		SDL_RenderFillRects(renderer, &cityDots[0], cityDots.size());
		
		SDL_RenderPresent(renderer);
		
		/*
		if(renderer == NULL){
			SDL_RenderDrawLine(renderer, g*10, g, 250, 250);	
		}
		*/
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

}
