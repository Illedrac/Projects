#pragma once
#include "Algorithm.h"

class InsertionSort : public Algorithm {
public:
	InsertionSort();
	std::vector<int> sortArray();

	int insertionSortTempValue;

};

