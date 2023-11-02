#include "AlgorithmFactory.h"
#include "InsertionSort.h"

Algorithm* AlgorithmFactory::CreateAlgorithm(AlgorithmType type, int screen_width, int unsorted_array_size)
{
    switch (type) {
    case AlgorithmType::INSERTION_SORT:
        return new InsertionSort(screen_width, unsorted_array_size);
        break;
    }

}