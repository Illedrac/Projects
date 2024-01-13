#pragma once
#include "Search_Algorithm.h"

class Search_Algorithm_Factory {

public:
	Search_Algorithm_Factory();
	Search_Algorithm_Factory(GameBoard* gb);

	Search_Algorithm* CreateAlgorithmImplementation(const SEARCH_ALGORITHM_TYPE& type);

private:
	GameBoard* game_board;
};