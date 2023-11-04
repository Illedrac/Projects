#pragma once
#include "Algorithm.h"

class QuickSort : public Algorithm{
public:
	QuickSort(int screen_width, int unsorted_array_size);
	
	bool SortArray(SDL_Window* window, SDL_Renderer* renderer);
	bool SortArray(SDL_Window* window, SDL_Renderer* renderer, int low, int high);
	bool SortArrayLR(SDL_Window* window, SDL_Renderer* renderer, int low, int high);
	int Partition(SDL_Window* window, SDL_Renderer* renderer, int low, int high);
	int PartitionLR(SDL_Window* window, SDL_Renderer* renderer, int low, int high);

private:
	int screen_width;

};