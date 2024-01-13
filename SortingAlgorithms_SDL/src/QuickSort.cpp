#include "QuickSort.h"
#include <algorithm>

QuickSort::QuickSort(int screen_width, int unsorted_array_size) :
    screen_width(screen_width)
{
    CreateUnsortedArray(unsorted_array_size);
}


int QuickSort::Partition(SDL_Window* window, SDL_Renderer* renderer, int low, int high)
{
    //choose the pivot

    int pivot = unsortedNumbersArray->at(high);
    
    DrawCurrentArrayAtIndex(window, renderer, high, screen_width, SDL_Color{0, 255, 255, 255});
    SDL_RenderPresent(renderer);
    
    if (!CheckSDLEvents())
        return -1;

    //SDL_Delay(15);

    

    //Index of smaller element and Indicate
    //the right position of pivot found so far
    int i = low - 1;
    for (int j = low; j <= high; j++)
    {

        if (!CheckSDLEvents())
            return -1;


        //If current element is smaller than the pivot
        if (unsortedNumbersArray->at(j) < pivot)
        {
            //Increment index of smaller element
            i++;

            ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);

            DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 255, 0, 0, 255 });
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 0, 255, 0, 255 });

            SDL_RenderPresent(renderer);
            SDL_Delay(2);

            std::swap(unsortedNumbersArray->at(i), unsortedNumbersArray->at(j));
            
            ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);

            DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 0, 255, 0, 255 });
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 255, 0, 0, 255 });

            SDL_RenderPresent(renderer);
            SDL_Delay(2);

            ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);
            
            DrawCurrentArrayAtIndex(window, renderer, j, screen_width, SDL_Color{ 255, 255, 255, 255 });
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width, SDL_Color{ 255, 255, 255, 255 });
            
            SDL_RenderPresent(renderer);
            SDL_Delay(2);
        }
    }
    DrawCurrentArrayAtIndex(window, renderer, high, screen_width, SDL_Color{ 255, 255, 255, 255 });



    ClearCurrentArrayAtIndex(window, renderer, i + 1, screen_width);
    ClearCurrentArrayAtIndex(window, renderer, high, screen_width);

    DrawCurrentArrayAtIndex(window, renderer, i + 1, screen_width, SDL_Color{ 255, 0, 0, 255 });
    DrawCurrentArrayAtIndex(window, renderer, high , screen_width, SDL_Color{ 0, 255, 0, 255 });

    SDL_RenderPresent(renderer);
    SDL_Delay(2);

    std::swap(unsortedNumbersArray->at(i + 1), unsortedNumbersArray->at(high));

    ClearCurrentArrayAtIndex(window, renderer, i + 1, screen_width);
    ClearCurrentArrayAtIndex(window, renderer, high, screen_width);

    DrawCurrentArrayAtIndex(window, renderer, i + 1, screen_width, SDL_Color{ 0, 255, 0, 255 });
    DrawCurrentArrayAtIndex(window, renderer, high, screen_width, SDL_Color{ 255, 0, 0, 255 });

    SDL_RenderPresent(renderer);
    SDL_Delay(2);

    ClearCurrentArrayAtIndex(window, renderer, i + 1, screen_width);
    ClearCurrentArrayAtIndex(window, renderer, high, screen_width);

    DrawCurrentArrayAtIndex(window, renderer, i + 1, screen_width, SDL_Color{ 255, 255, 255, 255 });
    DrawCurrentArrayAtIndex(window, renderer, high, screen_width, SDL_Color{ 255, 255, 255, 255 });

    SDL_RenderPresent(renderer);
    SDL_Delay(2);
    
    return (i + 1);
}

// The Quicksort function Implement
bool QuickSort::SortArray(SDL_Window* window, SDL_Renderer* renderer, int low, int high) {
    

    bool should_continue = CheckSDLEvents();
    if (!should_continue)
        return false;

    // when low is less than high
    if (low < high)
    {
        // pi is the partition return index of pivot

        int pi = Partition(window, renderer, low, high);

        if (pi == -1) return false;
        //Recursion Call
        //smaller element than pivot goes left and
        //higher element goes right
        SortArray(window, renderer, low, pi - 1);
        SortArray(window, renderer, pi + 1, high);
    }
    return true;
}

bool QuickSort::SortArray(SDL_Window* window, SDL_Renderer* renderer) {
    bool res = SortArray(window, renderer, 0, unsortedNumbersArray->size() - 1);//SortArray(window, renderer, 0, unsortedNumbersArray->size() - 1);
    isSorted = true;
    return res;
}

