#pragma once
#include <stack>
#include "Search_Algorithm.h"

class GameBoard;
class Edge;

class DFS_Algorithm : public Search_Algorithm {

public:
	DFS_Algorithm(GameBoard* gB);

	bool BeginSearch();
	bool Search(int row, int col);

private:
	std::stack<Edge> stack;
};