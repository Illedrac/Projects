#include "GameBoard.h"
#include "SDL.h"

GameBoard::GameBoard() :
    game_board_vector(number_cells, std::vector<CELL_TYPE>(number_cells, CELL_TYPE::EMPTY))
{
}

void GameBoard::DrawInitialBoard(SDL_Renderer* renderer,
								 const int cell_width_px,
								 const int cell_height_px)
{
	int line_between_cells_offset_px = 1;

	SDL_Color c;

	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;

	for (int row = 0; row < number_cells; row++) {
		for (int col = 0; col < number_cells; col++) {


			/*
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
			}*/


			SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

			SDL_Rect cur_rect;
			cur_rect.x = cell_width_px * col + line_between_cells_offset_px;
			cur_rect.y = cell_height_px * row + line_between_cells_offset_px;
			cur_rect.w = cell_width_px - line_between_cells_offset_px;
			cur_rect.h = cell_height_px - line_between_cells_offset_px;

			SDL_RenderFillRect(renderer, &cur_rect);
		}

	}
}