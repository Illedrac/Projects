#pragma once
#include "Algorithm.h"

class InsertionSort : public Algorithm {
public:
	InsertionSort(int width);

	void SortArray(SDL_Window* window, SDL_Renderer* renderer);
	void DrawCurrentArray(SDL_Window* window, SDL_Renderer* renderer);
	void DrawCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX);
	void ClearCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX);

};