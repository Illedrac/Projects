#include "BFS_Algorithm.h"
#include "GameBoard.h"
#include "Cell.h"


BFS_Algorithm::BFS_Algorithm(GameBoard* gB) :
	found_finish(false),
	game_board(gB),
	adjacency_matrix(),
	queue(),
	visited(),
	previous_map()
{
	CreateAdjacencyMatrix();
}

void BFS_Algorithm::BeginSearch() {
	Search(game_board->getStartRowPosition(), game_board->getStartColPosition());
}

void BFS_Algorithm::Search(int row, int col)
{

	Edge start(row, col);
	queue.push_front(start);
	visited.push_back(start);
	previous_map[std::make_pair(row, col)] = std::make_pair(-1,-1);

	game_board->DrawButDontDisplayCell(start.getRow(), start.getCol(), { 0, 255 , 0, 255 });

	game_board->DisplayRenderer();

	
	while (!queue.empty()) {
		Edge node = queue.front();
		queue.pop_front();
		

		int r = std::min(255.0, ( ( 1.0 / (game_board->getCellsHeight() - 1 ) * node.getRow() ) * 255 ) );
		int b = std::min(255.0, ((1.0 / (game_board->getCellsWidth() - 1) * node.getCol()) * 255)); 
		int g = 10; // 255 / (r + b + 1);

		/*
		game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), { 0, 0, 255, 255 });

		game_board->DisplayRenderer();

		game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), { 50, 50, 100, 255 });
		*/

		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 255;

		if (node.getRow() != game_board->getStartRowPosition() || node.getCol() != game_board->getStartColPosition() ) {
			game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), color);

			game_board->DisplayRenderer();
		}
		//SDL_Delay(10);

		//game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), { std::max(45, (double) r / 2), 100, 100, 255});

		/*
		
		game_board->DrawButDontDisplayCell(node.getRow(), node.getCol(), {255, 255, 255, 255});

		game_board->DisplayRenderer();

		*/
		int adjacency_value = (game_board->getCellsWidth() * node.getRow()) + node.getCol();

		std::vector<Edge> adjacent_edges = GetAdjacentEdges(adjacency_value, visited);

		for (int i = 0; i < adjacent_edges.size(); i++) {
	
			Edge edge = adjacent_edges.at(i);

			previous_map[std::make_pair(edge.getRow(), edge.getCol())] = std::make_pair(node.getRow(), node.getCol());

			if (edge.getRow() == game_board->getFinishRowPosition() && edge.getCol() == game_board->getFinishColPosition()) {
				
				DrawFinishedPath(edge.getRow(), edge.getCol());
				
				found_finish = true;
				
				return;
			}
						
			queue.push_back(edge);
			visited.push_back(edge);
		}
	}
}

void BFS_Algorithm::DrawFinishedPath(const int& row, const int& col) {

	int tempRow = row;
	int tempCol = col;
	while (previous_map[std::make_pair(tempRow, tempCol)] != std::make_pair(-1,-1)) {
		
		if(tempRow != row || tempCol != col){
			game_board->DrawButDontDisplayCell(tempRow, tempCol, {255, 155, 0, 255});
			game_board->DisplayRenderer();
		}

		std::pair<int, int> tempPair = previous_map.at(std::make_pair(tempRow, tempCol));
		tempRow = tempPair.first;
		tempCol = tempPair.second;

		SDL_Delay(5);
	}

	//game_board->DrawButDontDisplayCell(tempRow, tempCol, {255, 255, 0, 255});

	//game_board->DisplayRenderer();
}

// Could probably be optimized
void BFS_Algorithm::CreateAdjacencyMatrix() {

	int adjacency_one_dimension_length = (game_board->getCellsHeight() * game_board->getCellsWidth());

	for (int r = 0; r < game_board->getCellsHeight(); r++) {
	
		for (int c = 0; c < game_board->getCellsWidth(); c++) {
		
			int cur_value = (game_board->getCellsWidth() * r) + c;

			std::vector<int> temp(adjacency_one_dimension_length, 0);

			// Add the one below
			if( r != game_board->getCellsHeight() - 1 )
				temp.at(cur_value + game_board->getCellsWidth()) = 1;
			
			// Add the one above
			if( r != 0 )
				temp.at(cur_value - game_board->getCellsWidth()) = 1;

			// Add the one to the right
			if( c != game_board->getCellsWidth() - 1)				
				temp.at(cur_value + 1) = 1;
			
			// Add the one to the left
			if (c != 0)
				temp.at(cur_value - 1) = 1;

			adjacency_matrix.push_back(temp);

		}

	}
}


std::vector<Edge> BFS_Algorithm::GetAdjacentEdges(int& adjacency_value, std::vector<Edge>& visted) {
	
	std::vector<Edge> adjacent_edges;

	

	for (int i = 0; i < adjacency_matrix.at(adjacency_value).size(); i++) {
		
		if (adjacency_matrix.at(adjacency_value).at(i) == 1) {
		
			int adjacent_col = i % game_board->getCellsWidth();
			int adjacent_row = (i - adjacent_col) / game_board->getCellsWidth();
			
			if (!game_board->gameBoard.at(adjacent_row).at(adjacent_col).isCellAWall() && 
				!game_board->gameBoard.at(adjacent_row).at(adjacent_col).isCellStart() &&
				!HasBeenVisited(adjacent_row, adjacent_col) && 
				!IsInQueue(adjacent_row, adjacent_col))
			{
				Edge temp(adjacent_row, adjacent_col);
				adjacent_edges.push_back(temp);
			}
		}
	}

	return adjacent_edges;
}


bool BFS_Algorithm::HasBeenVisited(int row, int col) {

	for (Edge& cur_edge : getVisited()) {
		if (cur_edge.getRow() == row && cur_edge.getCol() == col) return true;
	}

	return false;
}

bool BFS_Algorithm::IsInQueue(int row, int col) {

	for (Edge& cur_edge : getQueue()) {
		if (cur_edge.getRow() == row && cur_edge.getCol() == col) return true;
	}

	return false;
}