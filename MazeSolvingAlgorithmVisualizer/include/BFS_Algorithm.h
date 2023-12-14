#pragma once
#include <vector>
#include <set>
#include <tuple>
#include "SDL.h"
class GameBoard;
class Edge;
class Cell;

class BFS_Algorithm {

public:
	BFS_Algorithm(GameBoard* gB);
	
	void BeginSearch();
	void Search(int row, int col);
	void CreateAdjacencyMatrix();
	std::vector<Edge> GetAdjacentEdges(Edge& cur_edge);
	void DisplayCurrentEdge(Edge& cur_edge);


private:
	bool found_finish;
	GameBoard* game_board;
	std::vector<std::vector<int>> adjacency_matrix;
	// I don't know what to name this


};