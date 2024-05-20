#include "GameBoard.h"
#include "SDL.h"

GameBoard::GameBoard(const int screen_width_px,
					 const int screen_height_px) :
    game_board_vector(number_cells, std::vector<CELL_TYPE>(number_cells, CELL_TYPE::EMPTY)),
	cell_width_px(screen_height_px / number_cells),
	cell_height_px(screen_height_px / number_cells),
	foodExists(false),
	is_screen_initialized(false),
	foodX(-1),
	foodY(-1),
	x_cell_offset( (screen_width_px / 2) - (cell_height_px * (number_cells / 2))),
	screen_width_px(screen_width_px),
	screen_height_px(screen_height_px)
{
}

void GameBoard::InitScreenToPlayGame(SDL_Renderer* renderer)
{
	
	//Fill in a black screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	SDL_Rect center_white_rectangle;
	center_white_rectangle.x = x_cell_offset;
	center_white_rectangle.y = 0;
	center_white_rectangle.w = screen_width_px - 2 * x_cell_offset + cell_width_px + line_between_cells_offset_px;
	center_white_rectangle.h = screen_height_px - 4;

	//Draw the center white rectangle
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &center_white_rectangle);

	is_screen_initialized = true;

}

void GameBoard::Reset() 
{
	ResetGameBoardVector();

	foodExists = false;
	foodX = -1;
	foodY = -1;
}

void GameBoard::ResetGameBoardVector()
{
	for (int i = 0; i < game_board_vector.size(); i++) 
	{
		
		for (int j = 0 ; j < game_board_vector.at(0).size(); j++)
		{
			
			setCellType(i, j, EMPTY);
		}
	}
}

void GameBoard::DrawBoard(SDL_Renderer* renderer)
{
	
	
	for (int row = 0; row < number_cells; row++) {
		for (int col = 0; col < number_cells; col++) {

			DrawBoardAtIndice(renderer, row, col);
		}
	}
	SDL_RenderPresent(renderer);
}

void GameBoard::DrawBoardAtIndice(SDL_Renderer* renderer, int row, int col)
{
	SDL_Color c = { 0,0,0,0 };

	switch (getCellType(row, col)) {
		case CELL_TYPE::EMPTY:
		{
			c.r = 0;
			c.g = 0;
			c.b = 0;
			c.a = 255;
			break;
		}
		case CELL_TYPE::FOOD:
		{
			c.r = 255;
			c.g = 0;
			c.b = 0;
			c.a = 255;
			break;
		}
		case CELL_TYPE::SNAKE:
		{
			c.r = 17;
			c.g = 186;
			c.b = 21;
			c.a = 255;
			break;
		}
	}


	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

	SDL_Rect cur_rect;
	cur_rect.x = cell_width_px * col + line_between_cells_offset_px + x_cell_offset;
	cur_rect.y = cell_height_px * row + line_between_cells_offset_px;
	cur_rect.w = cell_width_px - line_between_cells_offset_px;
	cur_rect.h = cell_height_px - line_between_cells_offset_px;

	SDL_RenderFillRect(renderer, &cur_rect);
}

