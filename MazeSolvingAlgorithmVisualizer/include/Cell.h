#pragma once
#include "SDL.h"

class Cell {

public:
	Cell(int cell_w_px, int cell_h_px);


	inline int getCellWidth() { return cell_width_px; }
	inline int getCellHeight() { return cell_height_px; }
	inline SDL_Color getCellColor() { return color; }

	inline int isCellAWall() { return is_a_wall; }
	inline int isCellStart() { return is_start; }
	inline int isCellFinish() { return is_finish; }

	void flipCellIsAWall();
	void flipCellStart();
	void flipCellFinish();
	void setCellColor(SDL_Color c);

private:
	int cell_width_px;
	int cell_height_px;
	bool is_a_wall;
	bool is_start;
	bool is_finish;
	SDL_Color color;
};