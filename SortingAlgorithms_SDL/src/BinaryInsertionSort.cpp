#include <iostream>
#include "BinaryInsertionSort.h"

BinaryInsertionSort::BinaryInsertionSort(int screen_width, int unsorted_array_size) :
    screen_width(screen_width),
    continue_running(true)

{
    CreateUnsortedArray(unsorted_array_size);
}


int BinaryInsertionSort::BinarySearch(int item, int low, int high)
{
    if (!continue_running) return -1;
    else continue_running = CheckSDLEvents();

    if (high <= low)
        return (item > unsortedNumbersArray->at(low)) ?
        (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == unsortedNumbersArray->at(mid))
        return mid + 1;

    if (item > unsortedNumbersArray->at(mid))
        return BinarySearch(item,
            mid + 1, high);
    return BinarySearch(item, low,
        mid - 1);
}

bool BinaryInsertionSort::SortArray(SDL_Window* window, SDL_Renderer* renderer)
{
    int i, loc, j, k, selected;
    
    for (i = 1; i < unsortedNumbersArray->size(); ++i)
    {
        j = i - 1;
        selected = unsortedNumbersArray->at(i);

        // find location where selected should be inserted
        loc = BinarySearch(selected, 0, j);
        if (loc == -1) return false;

        // Move all elements after location to create space
        while (j >= loc)
        {
            unsortedNumbersArray->at(j + 1) = unsortedNumbersArray->at(j);

            if (!continue_running) return false;
            else continue_running = CheckSDLEvents();

            ClearCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
            DrawCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
            SDL_RenderPresent(renderer);

            j--;
        }
        unsortedNumbersArray->at(j + 1) = selected;

        ClearCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, j + 1, screen_width);
        SDL_RenderPresent(renderer);
    }
    return true;
}