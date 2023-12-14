#include "Cell.h"

Cell::Cell(int cell_w_px, int cell_h_px) :
	cell_width_px(cell_w_px),
	cell_height_px(cell_h_px),
	is_a_wall(false),
	is_start(false),
	is_finish(false)
{
	color = { 255, 255, 255, 255 };
}

void Cell::flipCellIsAWall() {
	is_a_wall = !is_a_wall;
	if (is_a_wall) {
		color = { 0, 0, 0, 255 };
	}
	else {
		color = { 255, 255, 255, 255 };
	}
}

void Cell::flipCellStart() {
	if (!is_start) {
		SDL_Color color{ 0, 255, 0, 255 };
		setCellColor(color);
		is_start = true;
	}
	else {
		SDL_Color color{ 255, 255, 255, 255 };
		setCellColor(color);
		is_start = false;
	}
}

void Cell::flipCellFinish() {
	if (!is_finish) {
		SDL_Color color{ 255, 0, 0, 255 };
		setCellColor(color);
		is_finish = true;
	}
	else {
		SDL_Color color{ 255, 255, 255, 255 };
		setCellColor(color);
		is_finish = false;
	}
}

void Cell::setCellColor(SDL_Color c) {
	color = c;
}

