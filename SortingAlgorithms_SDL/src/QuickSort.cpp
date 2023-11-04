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
    //Index of smaller element and Indicate
    //the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j <= high; j++)
    {

        bool should_continue = CheckSDLEvents();
        if (!should_continue)
            return false;


        //If current element is smaller than the pivot
        if (unsortedNumbersArray->at(j) < pivot)
        {
            //Increment index of smaller element
            i++;

            std::swap(unsortedNumbersArray->at(i), unsortedNumbersArray->at(j));
            ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
            DrawCurrentArrayAtIndex(window, renderer, j, screen_width);
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width);

            SDL_RenderPresent(renderer);

        }
    }

    std::swap(unsortedNumbersArray->at(i + 1), unsortedNumbersArray->at(high));
    
    ClearCurrentArrayAtIndex(window, renderer, i + 1, screen_width);
    DrawCurrentArrayAtIndex(window, renderer, i + 1, screen_width);
    ClearCurrentArrayAtIndex(window, renderer, high, screen_width);
    DrawCurrentArrayAtIndex(window, renderer, high , screen_width);

    SDL_RenderPresent(renderer);

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

        //Recursion Call
        //smaller element than pivot goes left and
        //higher element goes right
        SortArray(window, renderer, low, pi - 1);
        SortArray(window, renderer, pi + 1, high);
    }
    return true;
}

bool QuickSort::SortArray(SDL_Window* window, SDL_Renderer* renderer) {
    bool res = SortArrayLR(window, renderer, 0, unsortedNumbersArray->size() - 1);//SortArray(window, renderer, 0, unsortedNumbersArray->size() - 1);
    return res;
}

bool QuickSort::SortArrayLR(SDL_Window* window, SDL_Renderer* renderer, int low, int high) {
    if (low < high) {
        int p = PartitionLR(window, renderer, low, high);
        SortArrayLR(window, renderer, low, p);
        SortArrayLR(window, renderer, p + 1, high);
    }

    return true;
}

int QuickSort::PartitionLR(SDL_Window* window, SDL_Renderer* renderer, int low, int high) {
    int pivot = unsortedNumbersArray->at(low);
    int i = low - 1;
    int j = high + 1;

    while (true) {
        i += 1;
        while(unsortedNumbersArray->at(i) < pivot) i += 1;
        j -= 1;
        while(unsortedNumbersArray->at(j) > pivot) j -= 1;
        //handleDrawing(array, j, high, low, -1)

        if (i >= j) return j;
        
        unsortedNumbersArray->at(i) = unsortedNumbersArray->at(j);
        unsortedNumbersArray->at(j) = unsortedNumbersArray->at(i);

        ClearCurrentArrayAtIndex(window, renderer, i, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, i, screen_width);
        ClearCurrentArrayAtIndex(window, renderer, j, screen_width);
        DrawCurrentArrayAtIndex(window, renderer, j, screen_width);

        SDL_RenderPresent(renderer);
    }
}


/*
def quickSort_LR(array, low, high):
    if low < high:
        p = partition(array, low, high)
        quickSort_LR(array, low, p)
        quickSort_LR(array, p + 1, high)

partition(array, low, high):
    pivot = unsortedNumbersArray->at(low]
    i = low - 1
    j = high + 1
    
    while True:
        i += 1
        while unsortedNumbersArray->at(i] < pivot: i += 1
        
        j -= 1
        while unsortedNumbersArray->at(j] > pivot: j -= 1
        
        handleDrawing(array, j, high, low, -1)
        if i >= j: return j
        unsortedNumbersArray->at(i], unsortedNumbersArray->at(j] = unsortedNumbersArray->at(j], unsortedNumbersArray->at(i]
*/