#include <iostream>
#include "InsertionSort.h"

InsertionSort::InsertionSort(int screen_width, int unsorted_array_size) :
    screen_width(screen_width)

{
    CreateUnsortedArray(unsorted_array_size);
}



bool InsertionSort::SortArray(SDL_Window* window, SDL_Renderer* renderer) {
    if (!isSorted) {
        int i, key, j;
        for (i = 1; i < unsortedNumbersArray->size(); i++) {
            
            key = unsortedNumbersArray->at(i);
            j = i - 1;

            while (j >= 0 && unsortedNumbersArray->at(j) > key) {
                unsortedNumbersArray->at(j + 1) = unsortedNumbersArray->at(j);
                j = j - 1;

                ClearCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
                DrawCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
                SDL_RenderPresent(renderer);

                bool should_continue = CheckSDLEvents();
                if(!should_continue)
                    return false;


            }
            unsortedNumbersArray->at(j + 1) = key;
        }
    }
    isSorted = false;
    return true;
}

