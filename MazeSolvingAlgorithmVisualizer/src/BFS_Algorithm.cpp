#include "BFS_Algorithm.h"
#include "GameBoard.h"
#include <future>

BFS_Algorithm::BFS_Algorithm(GameBoard* gB) :
	found_finish(false),
	game_board(gB),
	adjacency_matrix(),
	queue(),
	visited(),
	previous_map()
{
	const int total_number_threads = 15;

	std::vector< std::future< std::vector< std::vector<int> > > > futures(total_number_threads);

	for (int i = 0; i < total_number_threads; i++) {
		
		futures.at(i) = std::async(
									std::launch::async,
									[this, total_number_threads, i]() {
										return CreateAdjacencyMatrix(std::ref(total_number_threads), std::ref(i));
									}
							      );
	}								
	
	for (int i = 0; i < total_number_threads; i++) {
		std::vector<std::vector<int>> temp = futures.at(i).get();
		
		for (std::vector<int> temp1 : temp) {
			adjacency_matrix.push_back(temp1);
		}
	}

	//CreateAdjacencyMatrixOld();


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

	SDL_Event event;

	while (!queue.empty()) {

		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return false;
		}

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

		std::vector<Edge> adjacent_edges = GetAdjacentEdges(adjacency_value, visited);

		for (int i = 0; i < adjacent_edges.size(); i++) {
	
			Edge edge = adjacent_edges.at(i);

			current_pair_in_search = std::make_pair(edge.getRow(), edge.getCol());
			
			if(previous_map[current_pair_in_search] == default_pair)
				previous_map[current_pair_in_search] = std::make_pair(node.getRow(), node.getCol());

			if (edge.getRow() == game_board->getFinishRowPosition() && edge.getCol() == game_board->getFinishColPosition()) {
				
				DrawFinishedPath(edge.getRow(), edge.getCol());
				
				found_finish = true;
				
				return true;
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
			game_board->DrawButDontDisplayCell(tempRow, tempCol, {0, 255, 255, 255});
			game_board->DisplayRenderer();
		}

		std::pair<int, int> tempPair = previous_map.at(std::make_pair(tempRow, tempCol));
		tempRow = tempPair.first;
		tempCol = tempPair.second;

		SDL_Delay(5);
	}
}

std::vector<std::vector<int>> BFS_Algorithm::CreateAdjacencyMatrix(const int& total_number_threads, const int& thread_number) {
	
	int adjacency_one_dimension_length = (game_board->getCellsHeight() * game_board->getCellsWidth());

	int cells_width = game_board->getCellsWidth();

	if (adjacency_one_dimension_length % total_number_threads != 0) {
		SDL_Window* w = SDL_CreateWindow("", 500, 500, 1, 1, NULL);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "VECTOR LENGTH % NUMBER OF THREADS != 0", NULL);
	}

	int current_adjacency_value_start = (adjacency_one_dimension_length / total_number_threads) * thread_number;
	int current_adjacency_value_finish = (adjacency_one_dimension_length / total_number_threads) * (thread_number + 1);

	std::vector<std::vector<int>> result;

	for (int current_adjacency_value = current_adjacency_value_start;
		current_adjacency_value < current_adjacency_value_finish;
		current_adjacency_value++)
	{

		std::vector<int> temp_adjacency_values;
		
		// If it's not the on the left side, add the one to the left of it
		if (current_adjacency_value % cells_width != 0)
			temp_adjacency_values.push_back(current_adjacency_value - 1);

		// If it's not on the right side, add the one to the right of it
		if ((current_adjacency_value + 1) % cells_width != 0)
			temp_adjacency_values.push_back(current_adjacency_value + 1);

		// If it's not on the top row, add the one above it
		if (current_adjacency_value >= cells_width)
			temp_adjacency_values.push_back(current_adjacency_value - cells_width);

		// If it's not on the bottom row, add the one below it
		if (current_adjacency_value < ((game_board->getCellsHeight() - 1) * cells_width))
			temp_adjacency_values.push_back(current_adjacency_value + cells_width);

		result.push_back(temp_adjacency_values);
	}

	return result;

}


void BFS_Algorithm::CreateAdjacencyMatrixOld() {

	int adjacency_one_dimension_length = (game_board->getCellsHeight() * game_board->getCellsWidth());

	int cells_width = game_board->getCellsWidth();

	for (int adjacency_value = 0; adjacency_value < adjacency_one_dimension_length; adjacency_value++) {

		std::vector<int> temp_adjacency_values(adjacency_one_dimension_length, 0);

		// If it's not the on the left side, add the one to the left of it
		if (adjacency_value % cells_width != 0)
			temp_adjacency_values.at(adjacency_value - 1) = 1;

		// If it's not on the right side, add the one to the right of it
		if ((adjacency_value + 1) % cells_width != 0 || adjacency_value == 1)
			temp_adjacency_values.at(adjacency_value + 1) = 1;

		// If it's not on the top row, add the one above it
		if (adjacency_value >= cells_width)
			temp_adjacency_values.at(adjacency_value - cells_width) = 1;

		// If it's not on the bottom row, add the one below it
		if (adjacency_value < ((game_board->getCellsHeight() - 1) * cells_width))
			temp_adjacency_values.at(adjacency_value + cells_width) = 1;

		adjacency_matrix.push_back(temp_adjacency_values);
	}
}

std::vector<Edge> BFS_Algorithm::GetAdjacentEdges(int& adjacency_value, std::vector<Edge>& visted) {
	
	std::vector<Edge> adjacent_edges;

	
	for (int & cur: adjacency_matrix.at(adjacency_value)) {
		int adjacent_col = cur % game_board->getCellsWidth();
		int adjacent_row = (cur - adjacent_col) / game_board->getCellsWidth();
	
		if (!(game_board->gameBoard.at(adjacent_row).at(adjacent_col) == CELL_TYPE::WALL) &&
			!(game_board->gameBoard.at(adjacent_row).at(adjacent_col) == CELL_TYPE::START) &&
			!HasBeenVisited(adjacent_row, adjacent_col) &&
			!IsInQueue(adjacent_row, adjacent_col))
		{
			Edge temp(adjacent_row, adjacent_col);
			adjacent_edges.push_back(temp);
		}
	}
	
	return adjacent_edges;
}

std::vector<Edge> BFS_Algorithm::GetAdjacentEdgesOld(int& adjacency_value, std::vector<Edge>& visted) {

	std::vector<Edge> adjacent_edges;

	int adjacency_one_dimension_length = (game_board->getCellsHeight() * game_board->getCellsWidth());

	int cells_width = game_board->getCellsWidth();

	for (int i = 0; i < adjacency_matrix.at(adjacency_value).size(); i++) {

		if (adjacency_matrix.at(adjacency_value).at(i) == 1) {

			int adjacent_col = i % game_board->getCellsWidth();
			int adjacent_row = (i - adjacent_col) / game_board->getCellsWidth();

			if (! (game_board->gameBoard.at(adjacent_row).at(adjacent_col) == CELL_TYPE::WALL) &&
				! (game_board->gameBoard.at(adjacent_row).at(adjacent_col) == CELL_TYPE::START) &&
				! HasBeenVisited(adjacent_row, adjacent_col) &&
				! IsInQueue(adjacent_row, adjacent_col))
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

void BFS_Algorithm::ClearBoard() {
	found_finish = false;
	queue.clear();
	visited.clear();
	previous_map.clear();
}

