#pragma once
#include <vector>
#include <set>
#include <tuple>
#include "SDL.h"
#include "Edge.h"

class GameBoard;
class Edge;

class BFS_Algorithm {

public:
	BFS_Algorithm(GameBoard* gB);
	
	void BeginSearch();
	void Search(int row, int col);
	void DrawFinishedPath(Edge* finished_edge);
	void CreateAdjacencyMatrix();
	std::vector<Edge> GetAdjacentEdges(Edge& cur_edge, std::vector<Edge>& visted);
	bool HasBeenVisited(int row, int col);
	bool IsInQueue(int row, int col);

	inline std::vector<Edge> getQueue() { return queue; }
	inline std::vector<Edge> getVisited() { return visited; }

private:
	bool found_finish;
	GameBoard* game_board;
	std::vector<std::vector<int>> adjacency_matrix;
	std::vector<Edge> queue;
	std::vector<Edge> visited;


};