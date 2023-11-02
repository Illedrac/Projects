#pragma once
#include "Algorithm.h"

class AlgorithmFactory{
public:
    static Algorithm* CreateAlgorithm(AlgorithmType type, int screen_width, int unsorted_array_size);
};
