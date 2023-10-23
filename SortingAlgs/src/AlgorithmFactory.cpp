#include "AlgorithmFactory.h"
#include "InsertionSort.h"
#include "BubbleSort.h"

Algorithm* AlgorithmFactory::build(AlgorithmType type)
{
    switch (type) {
    case AlgorithmType::INSERTION_SORT:
        return new InsertionSort();
        break;
    case AlgorithmType::BUBBLE_SORT:
        return new BubbleSort();
        break;
    }

}