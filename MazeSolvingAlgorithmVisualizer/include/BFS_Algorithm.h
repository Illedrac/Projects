#pragma once
#include <vector>
#include <deque>
#include <map>
#include <utility>

#include "SDL.h"
#include "Edge.h"

class GameBoard;
class Edge;

class BFS_Algorithm {

public:
	BFS_Algorithm(GameBoard* gB);
	
	bool BeginSearch();
	bool Search(int row, int col);
	void DrawFinishedPath(const int& row, const int& col);
	void ClearBoard();

	std::vector<std::vector<int>> CreateAdjacencyMatrix(const int& total_number_threads, const int& thread_number);
	void CreateAdjacencyMatrixOld();
	std::vector<Edge> GetAdjacentEdges(int& adjacency_value, std::vector<Edge>& visted);
	std::vector<Edge> GetAdjacentEdgesOld(int& adjacency_value, std::vector<Edge>& visted);

	bool HasBeenVisited(int row, int col);
	bool IsInQueue(int row, int col);

	inline std::deque<Edge> getQueue() { return queue; }
	inline std::vector<Edge> getVisited() { return visited; }

private:
	bool found_finish;
	GameBoard* game_board;
	std::vector<std::vector<int>> adjacency_matrix;
	std::deque<Edge> queue;
	std::vector<Edge> visited;

			// An Edge              The previous edge
	std::map<std::pair<int,int>, std::pair<int,int>> previous_map;

};