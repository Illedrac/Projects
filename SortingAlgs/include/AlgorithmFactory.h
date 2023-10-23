#pragma once
#include "Algorithm.h"

enum AlgorithmType {
	INSERTION_SORT,
	BUBBLE_SORT
};

class Algorithm;

class AlgorithmFactory{
public:
    static Algorithm* build(AlgorithmType type);
};
