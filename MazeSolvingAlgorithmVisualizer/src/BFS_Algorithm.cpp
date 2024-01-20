#include "BFS_Algorithm.h"

BFS_Algorithm::BFS_Algorithm(GameBoard* gB) :
	Search_Algorithm(gB)
{
}

bool BFS_Algorithm::BeginSearch() {
	return Search(game_board->getStartRowPosition(), game_board->getStartColPosition());
}

bool BFS_Algorithm::Search(int row, int col)
{

	Edge start(row, col);
	queue.push_front(start);
	visited.push_back(start);
	previous_map[std::make_pair(row, col)] = std::make_pair(-1,-1);

	std::pair<int, int> default_pair = std::make_pair(0, 0);
	std::pair<int, int> current_pair_in_search;

	game_board->DrawButDontDisplayCell(start.getRow(), start.getCol(), { 0, 255 , 0, 255 });

	game_board->DisplayRenderer();

	
	while (!queue.empty()) {

		if ( !CheckSDLEvents() ) 
			return false;

		Edge node = queue.front();
		queue.pop_front();
		

		int r = std::min(255.0, ( ( 1.0 / (game_board->getCellsHeight() - 1 ) * node.getRow() ) * 255 ) );
		int b = std::min(255.0, ((1.0 / (game_board->getCellsWidth() - 1) * node.getCol()) * 255)); 
		int g = 10; 

		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 255;

		if (node.getRow() != game_board->getStartRowPosition() || node.getCol() != game_board->getStartColPosition() ) {
			game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), color);

			game_board->DisplayRenderer();

		}

		int adjacency_value = (game_board->getCellsWidth() * node.getRow()) + node.getCol();

		std::vector<Edge> adjacent_edges = GetAdjacentEdges(adjacency_value);

		for (int i = 0; i < adjacent_edges.size(); i++) {
	
			Edge edge = adjacent_edges.at(i);

			current_pair_in_search = std::make_pair(edge.getRow(), edge.getCol());
			
			if(previous_map[current_pair_in_search] == default_pair)
				previous_map[current_pair_in_search] = std::make_pair(node.getRow(), node.getCol());

			if (edge.getRow() == game_board->getFinishRowPosition() && edge.getCol() == game_board->getFinishColPosition()) {

				found_finish = true;

				DrawFinishedPath(edge.getRow(), edge.getCol());
				
				return true;
			}
						
			queue.push_back(edge);
			visited.push_back(edge);
		}
	}
	return true;
}



