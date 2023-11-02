#include "AlgorithmFactory.h"
#include "InsertionSort.h"
#include "SelectionSort.h"

Algorithm* AlgorithmFactory::CreateAlgorithm(AlgorithmType type, int screen_width, int unsorted_array_size)
{
    switch (type) {
    case AlgorithmType::INSERTION_SORT:
        return new InsertionSort(screen_width, unsorted_array_size);
        break;
    case AlgorithmType::SELECTION_SORT:
        return new SelectionSort(screen_width, unsorted_array_size);
    }

}