#include "GameBoard.h"
#include <random>
#include <ctime>

GameBoard::GameBoard(SDL_Window* window,
					 SDL_Renderer* renderer,
					 int num_cells_width,
					 int num_cells_height,
					 int screen_w_px,
					 int screen_h_px) :
	update_made(true),
	window(window),
	renderer(renderer),
	screen_width_px(screen_w_px),
	screen_height_px(screen_h_px),
	number_cells_width(num_cells_width),
	number_cells_height(num_cells_height),
	start_row_position(-1),
	start_col_position(-1),
	finish_row_position(-1),
	finish_col_position(-1)
{
	InitializeGameBoard();
}


void GameBoard::InitializeGameBoard() {
	for (int row = 0; row < number_cells_height; row++) {

		std::vector<Cell> temp;

		for (int col = 0; col < number_cells_width; col++) {
			Cell temp_cell (screen_width_px / number_cells_width, screen_height_px / number_cells_height);

			temp.push_back(temp_cell);
		}

		gameBoard.push_back(temp);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_Rect rect;
		rect.x = 1;
		rect.y = 1;
		rect.w = ( screen_width_px / number_cells_width ) * number_cells_width + 1;
		rect.h = (screen_height_px / number_cells_height) * number_cells_height + 1;

		SDL_RenderDrawRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}
}

void GameBoard::DrawButDontDisplayCell(int row, int col, SDL_Color color) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	Cell cur_cell = gameBoard.at(row).at(col);

	SDL_Rect cur_rect;
	cur_rect.x = cur_cell.getCellWidth() * col + line_between_cells_offset_px;
	cur_rect.y = cur_cell.getCellHeight() * row + line_between_cells_offset_px;
	cur_rect.w = cur_cell.getCellWidth() - line_between_cells_offset_px;
	cur_rect.h = cur_cell.getCellHeight() - line_between_cells_offset_px;

	SDL_RenderFillRect(renderer, &cur_rect);
}

void GameBoard::DisplayRenderer() {
	SDL_RenderPresent(renderer);
}


void GameBoard::DrawGameBoard() {

	if(update_made){

		

		for (int row = 0; row < number_cells_height; row++) {
			for (int col = 0; col < number_cells_width; col++) {
		
				
				Cell curCell = gameBoard.at(row).at(col);

				SDL_SetRenderDrawColor(renderer, curCell.getCellColor().r, curCell.getCellColor().g, curCell.getCellColor().b, curCell.getCellColor().a);

				SDL_Rect cur_rect;
				cur_rect.x = curCell.getCellWidth() * col + line_between_cells_offset_px;
				cur_rect.y = curCell.getCellHeight() * row + line_between_cells_offset_px;
				cur_rect.w = curCell.getCellWidth() - line_between_cells_offset_px;
				cur_rect.h = curCell.getCellHeight() - line_between_cells_offset_px;

				SDL_RenderFillRect(renderer, &cur_rect);
			}

		}

		SDL_RenderPresent(renderer);

		update_made = false;
	}
}

void GameBoard::generateUniformRandNoise() {
	std::default_random_engine generator(std::time(nullptr));
	std::uniform_int_distribution<int> row_dist(0, number_cells_height - 1);
	std::uniform_int_distribution<int> col_dist(0, number_cells_width - 1);

	int arbitrary_number_walls_generated = (number_cells_height + number_cells_width) * 3 ;

	int tried = 0;

	for (int i = 0; i < arbitrary_number_walls_generated; i++) {
		
		if (tried > arbitrary_number_walls_generated * 2) return;

		int row = row_dist(generator);
		int col = col_dist(generator);

		if (!gameBoard.at(row).at(col).isCellAWall() &&
			!gameBoard.at(row).at(col).isCellStart() &&
			!gameBoard.at(row).at(col).isCellFinish())
		{
			gameBoard.at(row).at(col).flipCellIsAWall();
		}else {
			++tried;
			i--;
		}
			

		update_made = true;
		
	}

	DrawGameBoard();
}


void GameBoard::setStartPosition(int row, int col) {
	start_row_position = row;
	start_col_position = col;
}

void GameBoard::setFinishPosition(int row, int col) {
	finish_row_position = row;
	finish_col_position = col;
}