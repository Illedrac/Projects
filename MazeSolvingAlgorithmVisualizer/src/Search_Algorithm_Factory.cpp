#include "Search_Algorithm_Factory.h"
#include "BFS_Algorithm.h"
#include "DFS_Algorithm.h"

Search_Algorithm_Factory::Search_Algorithm_Factory()
	: game_board()
{}

Search_Algorithm_Factory::Search_Algorithm_Factory(GameBoard* gb)
	: game_board(gb)
{}

Search_Algorithm* Search_Algorithm_Factory::CreateAlgorithmImplementation(const SEARCH_ALGORITHM_TYPE& type) {
	switch (type) {
		case SEARCH_ALGORITHM_TYPE::BFS:
			return new BFS_Algorithm(game_board);
		case SEARCH_ALGORITHM_TYPE::DFS:
			return new DFS_Algorithm(game_board);
		default:
			return new BFS_Algorithm(game_board);
	}

	return new BFS_Algorithm(game_board);
	
}