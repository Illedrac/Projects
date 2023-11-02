#pragma once
#include "Algorithm.h"

class SelectionSort : public Algorithm {
public:
	SelectionSort(int screen_width, int unsorted_array_size);

	bool SortArray(SDL_Window* window, SDL_Renderer* renderer);

private:
	int screen_width;
};