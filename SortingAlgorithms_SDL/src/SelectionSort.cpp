#include <iostream>
#include "SelectionSort.h"

SelectionSort::SelectionSort(int screen_width, int unsorted_array_size) :
    screen_width(screen_width)

{
    CreateUnsortedArray(unsorted_array_size);
}



bool SelectionSort::SortArray(SDL_Window* window, SDL_Renderer* renderer) {
    for (int step = 0; step < unsortedNumbersArray->size() - 1; step++) {
        bool result = true;
        int min_idx = step;
        
        for (int i = step + 1; i < unsortedNumbersArray->size(); i++) {

            // To sort in descending order, change > to < in this line.
            // Select the minimum element in each loop.
            if (unsortedNumbersArray->at(i) < unsortedNumbersArray->at(min_idx))
                min_idx = i;

            if (result == false) return result;
            else result = CheckSDLEvents();
            
        }

        int temp = unsortedNumbersArray->at(min_idx);
        unsortedNumbersArray->at(min_idx) = unsortedNumbersArray->at(step);
        unsortedNumbersArray->at(step) = temp;

        ClearCurrentArrayAtIndex(window, renderer, min_idx, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, min_idx, screen_width);
        
        ClearCurrentArrayAtIndex(window, renderer, step, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, step, screen_width);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    isSorted = true;
}