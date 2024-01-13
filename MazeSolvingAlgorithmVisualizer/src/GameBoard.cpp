#include "GameBoard.h"
#include <random>
#include <ctime>

GameBoard::GameBoard() :
	update_made(false),
	window(),
	renderer(),
	screen_width_px(-1),
	screen_height_px(-1),
	number_cells_width(-1),
	number_cells_height(-1),
	cell_width_px(-1),
	cell_height_px(-1),
	start_row_position(-1),
	start_col_position(-1),
	finish_row_position(-1),
	finish_col_position(-1)
{}

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
	cell_width_px(screen_width_px / num_cells_width),
	cell_height_px(screen_height_px / num_cells_height),
	start_row_position(-1),
	start_col_position(-1),
	finish_row_position(-1),
	finish_col_position(-1)

{
	InitializeGameBoard();
}


void GameBoard::InitializeGameBoard() {
	
	for (int row = 0; row < number_cells_height; row++) {

		std::vector<CELL_TYPE> temp(number_cells_width, CELL_TYPE::NORMAL_PATH);

		gameBoard.push_back(temp);

	}

	// MOVED THIS OUTSIDE FOR LOOP
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect;
	rect.x = 1;
	rect.y = 1;
	rect.w = (screen_width_px );// *number_cells_width + 1;
	rect.h = (screen_height_px);// *number_cells_height + 1;

	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}

void GameBoard::DrawButDontDisplayCell(int row, int col, SDL_Color color) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect cur_rect;
	cur_rect.x = cell_width_px * col + line_between_cells_offset_px;
	cur_rect.y = cell_height_px * row + line_between_cells_offset_px;
	cur_rect.w = cell_width_px - line_between_cells_offset_px;
	cur_rect.h = cell_height_px - line_between_cells_offset_px;

	SDL_RenderFillRect(renderer, &cur_rect);
}

void GameBoard::DisplayRenderer() {
	SDL_RenderPresent(renderer);
}


void GameBoard::DrawGameBoard() {

	if(update_made){

		

		for (int row = 0; row < number_cells_height; row++) {
			for (int col = 0; col < number_cells_width; col++) {
		
				SDL_Color c;


				switch (gameBoard.at(row).at(col)) {
					case CELL_TYPE::NORMAL_PATH:
						c.r = 255;
						c.g = 255;
						c.b = 255;
						c.a = 255;
						break;
					case CELL_TYPE::WALL:
						c.r = 0;
						c.g = 0;
						c.b = 0;
						c.a = 255;
						break;
					case CELL_TYPE::START:
						c.r = 0;
						c.g = 255;
						c.b = 0;
						c.a = 255;
						break;
					case CELL_TYPE::FINISH:
						c.r = 255;
						c.g = 0;
						c.b = 0;
						c.a = 255;
						break;
				}


				SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

				SDL_Rect cur_rect;
				cur_rect.x = cell_width_px * col + line_between_cells_offset_px;
				cur_rect.y = cell_height_px * row + line_between_cells_offset_px;
				cur_rect.w = cell_width_px - line_between_cells_offset_px;
				cur_rect.h = cell_height_px - line_between_cells_offset_px;

				SDL_RenderFillRect(renderer, &cur_rect);
			}

		}

		SDL_RenderPresent(renderer);

		update_made = false;
	}
}

void GameBoard::setStartPosition(int row, int col) {
	start_row_position = row;
	start_col_position = col;

}

void GameBoard::setFinishPosition(int row, int col) {
	finish_row_position = row;
	finish_col_position = col;
	
}

void GameBoard::ClearBoard() {
	
	start_row_position = -1;
	start_col_position = -1;

	finish_row_position = -1;
	finish_col_position = -1;

	for (std::vector<CELL_TYPE>& cur : gameBoard) {
		cur.assign(cur.size(), CELL_TYPE::NORMAL_PATH);
	}
	update_made = true;
	DrawGameBoard();

}

void GameBoard::SetAllCellsToWalls() {

	start_row_position = -1;
	start_col_position = -1;

	finish_row_position = -1;
	finish_col_position = -1;

	for (int col = 0; col < number_cells_width; col++) {
		for (int row = 0; row < number_cells_height; row++) {
			gameBoard.at(row).at(col) = CELL_TYPE::WALL;
		}
	}
}

bool GameBoard::readyToStartSearch() {

	return start_row_position != -1  &&
		   start_col_position != -1  &&
   		   finish_col_position != -1 &&
		   finish_col_position != -1;
}