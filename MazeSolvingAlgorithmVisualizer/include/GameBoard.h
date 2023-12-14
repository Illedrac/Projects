#pragma once
#include <vector>
#include "SDL.h"
#include "Cell.h"

class GameBoard {

public:
	GameBoard(SDL_Window* window, 
			  SDL_Renderer* renderer,
			  int num_cells_width, 
			  int num_cells_height, 
			  int screen_w_px, 
			  int screen_h_px);

	void InitializeGameBoard();

	void DisplayRenderer();
	void DrawButDontDisplayCell(int row, int col, SDL_Color color);
	void DrawGameBoard();
	void generateUniformRandNoise();
	void setStartPosition(int row, int col);
	void setFinishPosition(int row, int col);

	inline int getLineBetweenCellsOffset() { return line_between_cells_offset_px; }
	inline int getCellsWidth() { return number_cells_width; }
	inline int getCellsHeight() { return number_cells_height; }
	inline int getScreenWidth() { return screen_width_px; }
	inline int getScreenHeight() { return screen_height_px; }
	inline int getStartRowPosition() { return start_row_position; }
	inline int getStartColPosition() { return start_col_position; }
	inline int getFinishRowPosition() { return finish_row_position; }
	inline int getFinishColPosition() { return finish_col_position; }


	std::vector<std::vector<Cell>> gameBoard;

	bool update_made;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int screen_width_px;
	int screen_height_px;
	int number_cells_width;
	int number_cells_height;

	int start_row_position;
	int start_col_position;

	int finish_row_position;
	int finish_col_position;

	int line_between_cells_offset_px = 1;
};