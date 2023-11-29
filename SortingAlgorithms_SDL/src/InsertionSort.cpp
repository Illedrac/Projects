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

            // Draw the current rectangle green
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 0, 255, 0, 255});
            // Draw the current rectangle that we're comparing to as red
            DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 255, 0, 0, 0 });

            //Present the renderer
            SDL_RenderPresent(renderer);
            
            // Draw both rectanglea (green & red), back to white, not presenting yet
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 255, 255, 255, 255});
            DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 255, 255, 255, 255 });

            SDL_Delay(10);
            

            while (j >= 0 && unsortedNumbersArray->at(j) > key) {

                // J + 1 is the green rectangle

                unsortedNumbersArray->at(j + 1) = unsortedNumbersArray->at(j);
                unsortedNumbersArray->at(j) = key;
                // Now the green rectangle should be at J

                ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
                ClearCurrentArrayAtIndex(window, renderer, j + 1, screen_width);

                DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 0, 255, 0, 255 });
                DrawCurrentArrayAtIndex(window, renderer, j + 1, screen_width, SDL_Color{ 255, 255, 255, 255 });
                
                if (j > 0) {
                    DrawCurrentArrayAtIndex(window, renderer, j - 1, screen_width, SDL_Color{ 255, 0, 0, 255 });
                }

                SDL_RenderPresent(renderer);
                SDL_Delay(10);

                DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 255, 255, 255, 255 });
                
                if (j > 0) {
                    DrawCurrentArrayAtIndex(window, renderer, j - 1, screen_width, SDL_Color{ 255, 255, 255, 255 });
                }
                
                j = j - 1;
                                
                if (j > 0) {
                    
                }

                bool should_continue = CheckSDLEvents();
                
                if(!should_continue)
                    return false;

            }
            unsortedNumbersArray->at(j + 1) = key;
        }
    }

    DrawCurrentArray(window, renderer, screen_width);

    isSorted = true;
    return true;
}

