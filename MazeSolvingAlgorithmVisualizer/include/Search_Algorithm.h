#pragma once
#include <vector>
#include "GameBoard.h"
#include <future>
#include <deque>
#include <map>
#include "SDL.h"
#include "Edge.h"


enum SEARCH_ALGORITHM_TYPE {
	BFS,
	DFS
};

class Search_Algorithm {

public:

	void ClearBoard();

	virtual bool BeginSearch() = 0;

protected:

	Search_Algorithm(GameBoard* gb);
	
	std::vector<std::vector<int>> CreateAdjacencyMatrix(const int& total_number_threads, const int& thread_number);
	void CreateAdjacencyMatrixOld();
	std::vector<Edge> GetAdjacentEdges(int& adjacency_value);
	std::vector<Edge> GetAdjacentEdgesOld(int& adjacency_value);

	bool HasBeenVisited(int row, int col);
	bool IsInQueue(int row, int col);
	
	inline std::deque<Edge> getQueue() { return queue; }
	inline std::vector<Edge> getVisited() { return visited; }

	void DrawFinishedPath(const int& row, const int& col);


	GameBoard* game_board;
	bool found_finish;
	std::vector<std::vector<int>> adjacency_matrix;
	std::deque<Edge> queue;
	std::vector<Edge> visited;
	// An Edge              The previous edge
	std::map<std::pair<int, int>, std::pair<int, int>> previous_map;
};