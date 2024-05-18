#pragma once
#include <vector>

const int number_cells = 25;
const int line_between_cells_offset_px = 1;
const int x_box_offset = 5;

enum CELL_TYPE {
	EMPTY,
	FOOD,
	SNAKE
};

struct SDL_Renderer;

class GameBoard {


public:
	
	GameBoard(const int cell_width_px,
			  const int cell_height_px);

	void DrawBoard(SDL_Renderer* renderer);
	void DrawBoardAtIndice(SDL_Renderer* renderer, int row, int col);

	void Reset();

	inline bool getFoodExist() { return foodExists; }
	inline void setFoodExist(bool val) { foodExists = val; }

	void setCellType(int x, int y, CELL_TYPE type);
	
	inline CELL_TYPE getCellType(int x, int y) { return game_board_vector.at(x).at(y); }

	inline int getNumberCells() { return number_cells; }

	inline size_t getMaxWidth() { return game_board_vector.size() - 1; }
	inline size_t getMaxHeight() { return game_board_vector.at(0).size() - 1; }

	inline bool IsOnFood(int x, int y) { return foodX == x && foodY == y;}

	inline void setFood(int x, int y) { foodX = x; foodY = y; }


private:

	void ResetGameBoardVector();

	std::vector<std::vector<CELL_TYPE>> game_board_vector;
	int cell_width_px;
	int cell_height_px;
	bool foodExists;

	int foodX;
	int foodY;
};