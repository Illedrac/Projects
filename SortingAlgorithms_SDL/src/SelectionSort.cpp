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
        
        ClearCurrentArrayAtIndex(window, renderer, step, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, step, screen_width, SDL_Color{0, 255, 0, 255});
        SDL_RenderPresent(renderer);

        
        SDL_Delay(2);

        for (int i = step + 1; i < unsortedNumbersArray->size(); i++) {

            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 255, 0, 0, 255 });
            SDL_RenderPresent(renderer);
            
            SDL_Delay(2);
            
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 255, 255, 255, 255 });

            // Select the minimum element in each loop.
            if (unsortedNumbersArray->at(i) < unsortedNumbersArray->at(min_idx))
                min_idx = i;

            // Event Handling
            if (result == false) return result;
            else result = CheckSDLEvents();
            
        }

        int temp = unsortedNumbersArray->at(min_idx);
        unsortedNumbersArray->at(min_idx) = unsortedNumbersArray->at(step);
        unsortedNumbersArray->at(step) = temp;

        ClearCurrentArrayAtIndex(window, renderer, step, screen_width);
        ClearCurrentArrayAtIndex(window, renderer, min_idx, screen_width);

        DrawCurrentArrayAtIndex(window, renderer, step, screen_width, SDL_Color{ 255, 0, 0, 255 });
        DrawCurrentArrayAtIndex(window, renderer, min_idx, screen_width, SDL_Color{ 0, 255, 0, 255 });
        
        SDL_RenderPresent(renderer);
        SDL_Delay(2);

        DrawCurrentArrayAtIndex(window, renderer, step, screen_width, SDL_Color{ 255, 255, 255, 255 });
        DrawCurrentArrayAtIndex(window, renderer, min_idx, screen_width, SDL_Color{ 255, 255, 255, 255 });

        SDL_RenderPresent(renderer);
        SDL_Delay(2);

        /*
        ClearCurrentArrayAtIndex(window, renderer, min_idx, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, min_idx, screen_width);
        
        ClearCurrentArrayAtIndex(window, renderer, step, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, step, screen_width);
        */
    }

    isSorted = true;
}