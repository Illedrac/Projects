#include <iostream>
#include "InsertionSort.h"

InsertionSort::InsertionSort(int width)
{
	CreateUnsortedArray(width);
}

void InsertionSort::DrawCurrentArray(SDL_Window* window, SDL_Renderer* renderer) {
	for (int i = 0; i < unsortedNumbersArray->size(); i++) {
        DrawCurrentArrayAtIndex(window, renderer, i);
	}
}

void InsertionSort::DrawCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.x = unsortedNumbersArray->size() - posX;
    rect.y = unsortedNumbersArray->at(posX);
    rect.w = 1;
    rect.h = 1000 - rect.y;
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void InsertionSort::ClearCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect;
    rect.x = unsortedNumbersArray->size() - posX;
    rect.y = 0;
    rect.w = 1;
    rect.h = 1000;
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void InsertionSort::SortArray(SDL_Window* window, SDL_Renderer* renderer) {
    if (!isSorted) {
        int i, key, j;
        for (i = 1; i < unsortedNumbersArray->size(); i++) {
            
            key = unsortedNumbersArray->at(i);
            j = i - 1;

            while (j >= 0 && unsortedNumbersArray->at(j) > key) {
                unsortedNumbersArray->at(j + 1) = unsortedNumbersArray->at(j);
                j = j - 1;

                ClearCurrentArrayAtIndex(window, renderer, j + 1);
                DrawCurrentArrayAtIndex(window, renderer, j + 1);
            }
            unsortedNumbersArray->at(j + 1) = key;
        }
    }
    isSorted = false;
}

