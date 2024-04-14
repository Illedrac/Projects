#pragma once
#include <vector>

const int number_cells = 75;

enum CELL_TYPE {
	EMPTY,
	FOOD,
	SNAKE
};

struct SDL_Renderer;

class GameBoard {


public:
	
	GameBoard();

	void DrawInitialBoard(SDL_Renderer* renderer,
						  const int cell_width_px,
						  const int cell_height_px);

private:

	std::vector<std::vector<CELL_TYPE>> game_board_vector;
		
};