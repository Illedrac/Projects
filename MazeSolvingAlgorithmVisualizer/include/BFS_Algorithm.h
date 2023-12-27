#pragma once
#include "Search_Algorithm.h"

class GameBoard;
class Edge;

class BFS_Algorithm : public Search_Algorithm{

public:
	BFS_Algorithm(GameBoard* gB);
	
	bool BeginSearch();
	bool Search(int row, int col);
		
	
};