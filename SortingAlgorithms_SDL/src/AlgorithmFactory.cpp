#include "AlgorithmFactory.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "BinaryInsertionSort.h"

Algorithm* AlgorithmFactory::CreateAlgorithm(AlgorithmType type, int screen_width, int unsorted_array_size)
{
    switch (type) {
    case AlgorithmType::INSERTION_SORT:
        return new InsertionSort(screen_width, unsorted_array_size);

    case AlgorithmType::SELECTION_SORT:
        return new SelectionSort(screen_width, unsorted_array_size);
    
    case AlgorithmType::BINARY_INSERTION_SORT:
        return new BinaryInsertionSort(screen_width, unsorted_array_size);
    }
    

}