#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <catch.hpp>
#include "genetic.h"
#include <SDL2/SDL.h>
#include <thread>
#include <memory>

void StartGA(GA *gaInst){
	gaInst->Execute(); 
}

int main(int argc, char *argv[]){	
	std::srand(std::time(0));

	int populationSize = std::stoi(argv[1]);
	int breederPercentage = std::stoi(argv[2]);
	int targetGeneration = std::stoi(argv[3]);
	int mutationPercentage = std::stoi(argv[4]);
	int mutationPower = std::stoi(argv[5]);

	/*
	int populationSize = 1000;
	int breederPercentage = 30;
	int targetGeneration = 100;
	int mutationPercentage = 20;
	int mutationPower = 2;
*/
	std::cout << "Settings:\nPopulation:" << populationSize << "\nBreed %:" << breederPercentage << "\nTarget generation:" << targetGeneration << "\nMutation %:" << mutationPercentage << "\n";
	
	//int result = Catch::Session().run( argc, argv );
	//GA gaInst("att48.tsp",populationSize, breederPercentage, targetGeneration, mutationPercentage, mutationPower);
	GA gaInst("att48.tsp",populationSize, breederPercentage, targetGeneration, mutationPercentage, mutationPower);
	
//	GA gaInst("att48.tsp",10000, 10, 1000, 15);
//	gaInst.Execute(); // CREATE NEW THREAD FOR THIS
	//std::shared_ptr<GA> gaInst(new GA("att48.tsp",10000, 10, 1000, 15));
	//GA gaInst("att48.tsp",1000, 40, 1000, 40);
	gaInst.Execute();

	/*
	bool quit=false;
	bool GArunning = false;
	SDL_Window *window = NULL;
	//SDL_Surface *surface;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("TSP Visualizer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,480,SDL_WINDOW_OPENGL);
	//surface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	
	
	SDL_Event e;
	int currentGen = 0;
	while(!quit){
		if(!GArunning){
			GArunning = true;
			std::thread ga(StartGA, &gaInst);
			ga.detach();
		}
		while(SDL_PollEvent( &e ) != 0){
			if( e.type == SDL_QUIT)
				quit = true;
		}
		
		if(currentGen != gaInst.getCurrentGeneration()){
			std::cout << "Window best: " << gaInst.getBest() << "\n";
			currentGen = gaInst.getCurrentGeneration();
		}
		
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255,0,0,255);
		SDL_RenderDrawLine(renderer, 0,0,250,250);
		SDL_RenderPresent(renderer);
	}
		
	SDL_DestroyWindow(window);
	SDL_Quit();
	*/
	return 0;
}
