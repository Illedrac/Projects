#include "GameBoard.h"
#include "SDL.h"

GameBoard::GameBoard(const int cell_width_px,
					 const int cell_height_px) :
    game_board_vector(number_cells, std::vector<CELL_TYPE>(number_cells, CELL_TYPE::EMPTY)),
	cell_width_px(cell_width_px),
	cell_height_px(cell_height_px),
	foodExists(false),
	foodX(-1),
	foodY(-1)
{
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
	SDL_Color c;

	for (int row = 0; row < number_cells; row++) {
		for (int col = 0; col < number_cells; col++) {


			DrawBoardAtIndice(renderer, row, col);
		}
	}
	SDL_RenderPresent(renderer);
}


void GameBoard::DrawBoardAtIndice(SDL_Renderer* renderer, int row, int col)
{
	SDL_Color c;

	switch (getCellType(row, col)) {
		case CELL_TYPE::EMPTY:
		{
			c.r = 255;
			c.g = 255;
			c.b = 255;
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
			c.r = 0;
			c.g = 255;
			c.b = 0;
			c.a = 255;
			break;
		}
	}


	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

	SDL_Rect cur_rect;
	cur_rect.x = cell_width_px * col + line_between_cells_offset_px + x_box_offset;
	cur_rect.y = cell_height_px * row + line_between_cells_offset_px;
	cur_rect.w = cell_width_px - line_between_cells_offset_px;
	cur_rect.h = cell_height_px - line_between_cells_offset_px;

	SDL_RenderFillRect(renderer, &cur_rect);
}


void GameBoard::setCellType(int x, int y, CELL_TYPE type) 
{ 
	game_board_vector.at(x).at(y) = type; 

	//DrawBoardAtIndice(renderer, x, y);
}