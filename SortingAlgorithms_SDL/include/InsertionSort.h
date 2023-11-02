#pragma once
#include "Algorithm.h"

class InsertionSort : public Algorithm {
public:
	InsertionSort(int screen_width, int unsorted_array_size);

	bool SortArray(SDL_Window* window, SDL_Renderer* renderer);
	
private:
	int screen_width;
};