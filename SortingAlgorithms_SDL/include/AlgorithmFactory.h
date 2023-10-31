#pragma once
#include "Algorithm.h"

class AlgorithmFactory{
public:
    static Algorithm* CreateAlgorithm(AlgorithmType type, int width);
};
