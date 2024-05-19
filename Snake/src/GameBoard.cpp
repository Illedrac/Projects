#include "GameBoard.h"
#include "SDL.h"

GameBoard::GameBoard(const int screen_width_px,
					 const int screen_height_px) :
    game_board_vector(number_cells, std::vector<CELL_TYPE>(number_cells, CELL_TYPE::EMPTY)),
	cell_width_px(screen_height_px / number_cells),
	cell_height_px(screen_height_px / number_cells),
	foodExists(false),
	foodX(-1),
	foodY(-1),
	x_cell_offset( (screen_width_px / 2) - (cell_height_px * (number_cells / 2))),
	screen_width_px(screen_width_px),
	screen_height_px(screen_height_px)
{
}

void GameBoard::InitScreen(SDL_Renderer* renderer)
{
	
	//Fill in a white screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	//SDL rect for the left and right black rectangles
	SDL_Rect left_right_black_rectangles;

	left_right_black_rectangles.x = 0;
	left_right_black_rectangles.y = 0;
	left_right_black_rectangles.w = x_cell_offset;
	left_right_black_rectangles.h = screen_height_px;

	//Draw the left rectangle
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &left_right_black_rectangles);

	//Update the X position and draw the right black rectangle
	left_right_black_rectangles.x = screen_width_px - x_cell_offset + cell_width_px + line_between_cells_offset_px;
	SDL_RenderFillRect(renderer, &left_right_black_rectangles);

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

