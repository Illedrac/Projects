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
	void ReorderAdjacentEdges(Edge& node, std::vector<Edge>& adjacent_edges);
	int getDirectionPrecedence(std::vector<int>& current_precedence_value);

private:
	std::stack<Edge> stack;

	const int number_possible_neighbors = 4;
	const int left[2] = { 0, -1 };
	const int up[2] = { -1, 0 };
	const int right[2] = { 0, 1 };
	const int down[2] = { 1, 0 };
	
	const int direction_precedence[4][2] = { 
											{ -1, 0 }, // Up
											{ 0, 1 },  // Right	
											{ 1, 0 },  // Down
											{ 0, -1 }  // Left										   
										    };

};