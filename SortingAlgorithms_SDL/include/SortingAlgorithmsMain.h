#include "SDL.h"
#include "AlgorithmFactory.h"

class SortingAlgorithmsMain {

public:
	SortingAlgorithmsMain(int width, int height);

	void Initialize(AlgorithmType algorithm_type, int width);
	void DrawInitialArray();
	void ClearScreen();

	SDL_Window* window ;
	SDL_Renderer* renderer ;
	
	Algorithm* sorting_algorithm_implementation;
};