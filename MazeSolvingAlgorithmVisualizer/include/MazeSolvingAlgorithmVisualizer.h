#pragma once
#include <memory>
#include "GameBoard.h"
#include "MazeGenerator.h"
#include "Search_Algorithm_Factory.h"
#include "ButtonContainer.h"

enum DRAW_TYPE {
	DRAW_MAZE,
	DRAW_START,
	DRAW_FINISH
};

class MazeSolvingAlgorithmVisualizer {

public:

	MazeSolvingAlgorithmVisualizer();
	void GameLoop();


private:
	SDL_Renderer* r;
	SDL_Window* w;

	std::shared_ptr<SDL_Renderer> renderer;
	std::shared_ptr<SDL_Window> window;

	ButtonContainer button_container;

	GameBoard board;

	MazeGenerator maze_generator;

	SEARCH_ALGORITHM_TYPE searchType;

	Search_Algorithm_Factory factory;

	Search_Algorithm* search_algorithm_implementation;


	const int screen_width_px = 1910;
	const int screen_height_px = 1040;
	const int number_cells_width = 175;
	const int number_cells_height = 198;

	DRAW_TYPE current_draw_type = DRAW_MAZE;

	bool continue_running_program = SDL_TRUE;
	bool mouse_button_held = false;
	bool finish_already_drawn = false;
	bool start_already_drawn = false;
};