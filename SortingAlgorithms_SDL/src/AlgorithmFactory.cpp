#include "AlgorithmFactory.h"
#include "InsertionSort.h"

Algorithm* AlgorithmFactory::CreateAlgorithm(AlgorithmType type, int width)
{
    switch (type) {
    case AlgorithmType::INSERTION_SORT:
        return new InsertionSort(width);
        break;
    }

}