#include "DFS_Algorithm.h"

DFS_Algorithm::DFS_Algorithm(GameBoard* gB) :
	Search_Algorithm(gB)
{

}

bool DFS_Algorithm::BeginSearch() {

    return Search(game_board->getStartRowPosition(), game_board->getStartColPosition());
}

bool DFS_Algorithm::Search(int row, int col) {
    
	Edge start(row, col);
	stack.push(start);
	visited.push_back(start);
	previous_map[std::make_pair(row, col)] = std::make_pair(-1, -1);

	std::pair<int, int> default_pair = std::make_pair(0, 0);
	std::pair<int, int> current_pair_in_search;

	game_board->DrawButDontDisplayCell(start.getRow(), start.getCol(), { 0, 255 , 0, 255 });

	game_board->DisplayRenderer();

	SDL_Event event;

	while (!stack.empty()) {

		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return false;
			case SDL_QUIT:
				return false;
		}

		Edge node = stack.top();
		stack.pop();


		int r = std::min(255.0, ((1.0 / (game_board->getCellsHeight() - 1) * node.getRow()) * 255));
		int b = std::min(255.0, ((1.0 / (game_board->getCellsWidth() - 1) * node.getCol()) * 255));
		int g = 10;

		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 255;

		if (node.getRow() != game_board->getStartRowPosition() || node.getCol() != game_board->getStartColPosition()) {
			game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), color);

			game_board->DisplayRenderer();
		}

		int adjacency_value = (game_board->getCellsWidth() * node.getRow()) + node.getCol();

		std::vector<Edge> adjacent_edges = GetAdjacentEdges(adjacency_value);
		
		if (adjacent_edges.size() > 1)
			ReorderAdjacentEdges(node, adjacent_edges);

		for (int i = 0; i < adjacent_edges.size(); i++) {

			Edge edge = adjacent_edges.at(i);

			current_pair_in_search = std::make_pair(edge.getRow(), edge.getCol());

			if (previous_map[current_pair_in_search] == default_pair)
				previous_map[current_pair_in_search] = std::make_pair(node.getRow(), node.getCol());

			if (edge.getRow() == game_board->getFinishRowPosition() && edge.getCol() == game_board->getFinishColPosition()) {

				DrawFinishedPath(edge.getRow(), edge.getCol());

				found_finish = true;

				return true;
			}

			stack.push(edge);
			visited.push_back(edge);
		}
	}
	return true;

}

// According to https://www.youtube.com/watch?v=GC-nBgi9r0U&t=241s
// The order of precedence for DFS ( at least his implementation ) is Up, Right, Down, Left
// Since we're using a stack, we want to push elements up in that order, just reversed
// Thus, reorganize the adjacency matrix such that the adjacent nodes are in the order of 
// Left, Down, Right, Up
void DFS_Algorithm::ReorderAdjacentEdges(Edge& node, std::vector<Edge>& adjacent_edges) {

	
	for (int i = 0; i < adjacent_edges.size(); i++) {
		
		Edge& cur_edge = adjacent_edges.at(i);

		int index_to_swap = -1;

		std::vector<int> current_precedence_value = { cur_edge.getRow() - node.getRow(), cur_edge.getCol() - node.getCol()};
		
		int highest_precedence_index = getDirectionPrecedence(current_precedence_value);

		for (int j = i + 1; j < adjacent_edges.size(); j++) {

			Edge& edge_to_compare_against = adjacent_edges.at(j);
			
			std::vector<int> comparison_precedence_value{ edge_to_compare_against.getRow() - node.getRow(),
														  edge_to_compare_against.getCol() - node.getCol() };

			int comparison_precedence_index = getDirectionPrecedence(comparison_precedence_value);

			if (comparison_precedence_index < highest_precedence_index) {
				highest_precedence_index = comparison_precedence_index;
				index_to_swap = j;
			}

		}

		if(index_to_swap != -1)
			std::swap(adjacent_edges.at(i), adjacent_edges.at(index_to_swap));
	}
	int x = 10;
}


int DFS_Algorithm::getDirectionPrecedence(std::vector<int>& current_precedence_value) {

	for (int i = 0; i < number_possible_neighbors; i++) {
		if (current_precedence_value.at(0) == direction_precedence[i][0] &&
			current_precedence_value.at(1) == direction_precedence[i][1])
		{
			return i;
		}
	}

	return -1;

}
