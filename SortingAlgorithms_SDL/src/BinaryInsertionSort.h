#pragma once
#pragma once
#include "Algorithm.h"

class BinaryInsertionSort : public Algorithm {
public:
	BinaryInsertionSort(int screen_width, int unsorted_array_size);

	bool SortArray(SDL_Window* window, SDL_Renderer* renderer);
	int BinarySearch(int item, int low, int high);

private:
	int screen_width;
	bool continue_running;
};