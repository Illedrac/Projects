#include <string>
#include <algorithm>
#include "SDL.h"
#include "GameBoard.h"
#include "Button.h"
#include "SDL_image.h"
#include "MazeGenerator.h"
#include "Search_Algorithm_Factory.h"

enum DRAW_TYPE {
	DRAW_MAZE,
	DRAW_START,
	DRAW_FINISH
};

// I don't really know how buttons should work in SDL2 so I just create button instances that hold a texture and 
// to check if a user clicks the button I just check x and y values of the mouse click. Not very good but the UI is not the
// focus of this project 
void CreateButtons(SDL_Renderer* renderer, std::vector<Button>& buttons, DRAW_TYPE current_draw_type) {
	
	Button Search_button(renderer, "Search_button", SDL_GetBasePath(), 10, BUTTON_TYPE::BUTTON_SEARCH);
	Button Start_button(renderer, "Start_button", SDL_GetBasePath(), 120, BUTTON_TYPE::BUTTON_START);
	Button Finish_button(renderer, "Finish_button", SDL_GetBasePath(), 230, BUTTON_TYPE::BUTTON_FINISH);
	Button Maze_button(renderer, "Maze_button", SDL_GetBasePath(), 340, BUTTON_TYPE::BUTTON_MAZE);
	Button Add_Walls_button(renderer, "Add_Walls_button", SDL_GetBasePath(), 450, BUTTON_TYPE::BUTTON_ADD_WALLS);
	Button Reset_button(renderer, "Reset_button", SDL_GetBasePath(), 560, BUTTON_TYPE::BUTTON_RESET);

	buttons.push_back(Search_button);
	buttons.push_back(Start_button);
	buttons.push_back(Finish_button);
	buttons.push_back(Maze_button);
	buttons.push_back(Add_Walls_button);
	buttons.push_back(Reset_button);


	// This should eventually be updated to be better, it kinda sucks atm
	switch (current_draw_type) {
		case DRAW_TYPE::DRAW_START:
			buttons.at(1).setSelected(true);
			break;
		case DRAW_TYPE::DRAW_FINISH:
			buttons.at(2).setSelected(true);
			break;
		case DRAW_TYPE::DRAW_MAZE:
			buttons.at(3).setSelected(true);
			break;
	}

}

void DrawButtons(SDL_Renderer* renderer, std::vector<Button>& buttons){

	for (Button b : buttons) {
		SDL_RenderCopy(renderer, b.getTexture(), NULL, &b.getRect());
	}
	
}

void DrawButtonForAMoment(SDL_Renderer* renderer, Button& b) {
	b.setSelected(true);
	SDL_RenderCopy(renderer, b.getTexture(), NULL, &b.getRect());
	SDL_RenderPresent(renderer);
	SDL_Delay(75);
	b.setSelected(false);
	SDL_RenderCopy(renderer, b.getTexture(), NULL, &b.getRect());
	SDL_RenderPresent(renderer);
}


void UnselectButton(BUTTON_TYPE type, std::vector<Button>& buttons) {
	switch (type) {
		case BUTTON_TYPE::BUTTON_SEARCH:
			buttons.at(0).setSelected(false);
			return;
		case BUTTON_TYPE::BUTTON_START:
			buttons.at(1).setSelected(false);
			return;
		case BUTTON_TYPE::BUTTON_FINISH:
			buttons.at(2).setSelected(false);
			return;
		case BUTTON_TYPE::BUTTON_MAZE:
			buttons.at(3).setSelected(false);
			return;
		case BUTTON_TYPE::BUTTON_ADD_WALLS:
			buttons.at(4).setSelected(false);
			return;
		case BUTTON_TYPE::BUTTON_RESET:
			buttons.at(5).setSelected(false);
			return;
	}
}

// This really needs to be cleaned up 
void GameLoop() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);

	SDL_Renderer* renderer;
	SDL_Window* window;

	std::vector<Button> buttons;

	const int screen_width_px = 1910;
	const int screen_height_px = 1040;
	const int number_cells_width = 175;
	const int number_cells_height = 198;


	SDL_CreateWindowAndRenderer(screen_width_px, screen_height_px, NULL, &window, &renderer);

	std::string path_to_font = SDL_GetBasePath();
	
	DRAW_TYPE current_draw_type = DRAW_MAZE;

	CreateButtons(renderer, buttons, current_draw_type);
	DrawButtons(renderer, buttons);

	GameBoard board(window, renderer, number_cells_width, number_cells_height, screen_width_px - 160, screen_height_px - 50);
	
	MazeGenerator maze_generator(&board);

	SEARCH_ALGORITHM_TYPE searchType = SEARCH_ALGORITHM_TYPE::DFS;

	Search_Algorithm_Factory factory(&board);

	Search_Algorithm* search_algorithm_implementation = factory.CreateAlgorithmImplementation(searchType);
	
	bool continue_running_program = SDL_TRUE;
	bool mouse_button_held = false;
	bool finish_already_drawn = false;
	bool start_already_drawn = false;

	BUTTON_TYPE selected_button;

	switch (current_draw_type) {
		case DRAW_TYPE::DRAW_START:
			selected_button = BUTTON_START;
			break;
		case DRAW_TYPE::DRAW_FINISH:
			selected_button = BUTTON_FINISH;
			break;
		case DRAW_TYPE::DRAW_MAZE:
			selected_button = BUTTON_MAZE;
			break;

	}

	SDL_Event event;
	
	int mouse_x, mouse_y;

	while (continue_running_program) {
		if(board.update_made)
			board.DrawGameBoard();
		SDL_PollEvent(&event);

		switch (event.type) {

		case SDL_KEYDOWN:
	
			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					
					continue_running_program = false;
					break;
				case SDL_SCANCODE_B:

					DrawButtonForAMoment(renderer, buttons.at(0));
					
					if (board.readyToStartSearch())
						continue_running_program = search_algorithm_implementation->BeginSearch();
					
					break;
				
				case SDL_SCANCODE_F:

					UnselectButton(selected_button, buttons);
					selected_button = BUTTON_TYPE::BUTTON_FINISH;
					current_draw_type = DRAW_TYPE::DRAW_FINISH;
					buttons.at(2).setSelected(true);
					DrawButtons(renderer, buttons);
					SDL_RenderPresent(renderer);
					break;
				
				case SDL_SCANCODE_M:

					UnselectButton(selected_button, buttons);
					selected_button = BUTTON_TYPE::BUTTON_MAZE;
					current_draw_type = DRAW_TYPE::DRAW_MAZE;
					buttons.at(3).setSelected(true);
					DrawButtons(renderer, buttons);
					SDL_RenderPresent(renderer);
					break;
				
				case SDL_SCANCODE_S:

					UnselectButton(selected_button, buttons);
					selected_button = BUTTON_TYPE::BUTTON_START;
					current_draw_type = DRAW_START;
					buttons.at(1).setSelected(true);
					DrawButtons(renderer, buttons);
					SDL_RenderPresent(renderer);
					break;
				
				case SDL_SCANCODE_R:
				
					DrawButtonForAMoment(renderer, buttons.at(5));

					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

					SDL_RenderClear(renderer);

					UnselectButton(selected_button, buttons);

					selected_button = BUTTON_TYPE::BUTTON_MAZE;
					current_draw_type = DRAW_TYPE::DRAW_MAZE;
					buttons.at(3).setSelected(true);
					DrawButtons(renderer, buttons);

					board.ClearBoard();
					search_algorithm_implementation->ClearBoard();

					for (Button& b : buttons) {
						b.setSelected(false);
					}

					// Instead of having booleans for these we could just check if the boards stored finish & start positions are -1, -1
					finish_already_drawn = false;
					start_already_drawn = false;
					break;
				case SDL_SCANCODE_G:
					
					DrawButtonForAMoment(renderer, buttons.at(4));
					maze_generator.generate();
					break;

				default:
					break;
			}

			break;
		case SDL_QUIT:
			continue_running_program = SDL_FALSE;
			break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {

				SDL_GetMouseState(&mouse_x, &mouse_y);

				if (mouse_x >= 0 && mouse_x < board.getScreenWidth() && mouse_y >= 0 && mouse_y < board.getScreenHeight()) {
					
					mouse_y = std::max(mouse_y, 0);
					mouse_x = std::max(mouse_x, 0);

					mouse_y = std::min(mouse_y, board.getScreenHeight());
					mouse_x = std::min(mouse_x, board.getScreenWidth());

					int row_index = (mouse_y - board.getLineBetweenCellsOffset()) / board.getCellHeightPx();
					int col_index = (mouse_x - board.getLineBetweenCellsOffset()) / board.getCellWidthPx();


					if (row_index < 0 || row_index >= board.getCellsHeight() || col_index < 0 || col_index >= board.getCellsWidth())
						break;

					bool initial_button_state = board.gameBoard.at(row_index).at(col_index) == CELL_TYPE::WALL;


					if (current_draw_type == DRAW_MAZE) {

						while (true) {

							SDL_GetMouseState(&mouse_x, &mouse_y);

							mouse_y = std::max(mouse_y, 0);
							mouse_x = std::max(mouse_x, 0);

							mouse_y = std::min(mouse_y, board.getScreenHeight());
							mouse_x = std::min(mouse_x, board.getScreenWidth());

							row_index = (mouse_y - board.getLineBetweenCellsOffset()) / board.getCellHeightPx();
							col_index = (mouse_x - board.getLineBetweenCellsOffset()) / board.getCellWidthPx();

							row_index = std::min(row_index, board.getCellsHeight() - 1);
							col_index = std::min(col_index, board.getCellsWidth() - 1);

							bool currentCellIsAWall = board.gameBoard.at(row_index).at(col_index) == CELL_TYPE::WALL;
							if (  currentCellIsAWall == initial_button_state) {

								if (currentCellIsAWall) {
									board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
								}
								else {
									board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::WALL;
								}
								
								board.update_made = true;

								board.DrawGameBoard();
							}

							SDL_PollEvent(&event);
							if (event.type == SDL_MOUSEBUTTONUP) break;
						}

					}
					else if (current_draw_type == DRAW_START) {
						
						if (board.getStartRowPosition() != -1 || board.getStartColPosition() != -1) {
							board.gameBoard.at(board.getStartRowPosition()).at(board.getStartColPosition()) = CELL_TYPE::NORMAL_PATH;
						}
						else 
							start_already_drawn = true;

						board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::START;
						board.setStartPosition(row_index, col_index);

						board.update_made = true;

						board.DrawGameBoard();
						
						
					}
					else if (current_draw_type == DRAW_FINISH) {
						if (board.getFinishRowPosition() != -1 || board.getFinishColPosition() != -1) {
							board.gameBoard.at(board.getFinishRowPosition()).at(board.getFinishColPosition()) = CELL_TYPE::NORMAL_PATH;
						}
						else
							start_already_drawn = true;

						board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::FINISH;
						board.setFinishPosition(row_index, col_index);

						board.update_made = true;

						board.DrawGameBoard();
					}
				}
				

				else {
					for (Button& b : buttons) {
						SDL_Rect& rect = b.getRect();

						if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w) && mouse_y >= rect.y && mouse_y <= (rect.y + rect.h)) {
							
							UnselectButton(selected_button, buttons);

							switch (b.getButtonType()) {
								case BUTTON_TYPE::BUTTON_SEARCH:
									
									DrawButtonForAMoment(renderer, b);
									
									if(board.readyToStartSearch())
										continue_running_program = search_algorithm_implementation->BeginSearch();
									break;

								case BUTTON_TYPE::BUTTON_START:
									
									selected_button = BUTTON_TYPE::BUTTON_START;
									current_draw_type = DRAW_TYPE::DRAW_START;
									b.setSelected(true);
									DrawButtons(renderer, buttons);
									SDL_RenderPresent(renderer);
									break;

								case BUTTON_TYPE::BUTTON_FINISH:
									
									selected_button = BUTTON_TYPE::BUTTON_FINISH;
									current_draw_type = DRAW_TYPE::DRAW_FINISH;
									b.setSelected(true);
									DrawButtons(renderer, buttons);
									SDL_RenderPresent(renderer);
									break;
								
								case BUTTON_TYPE::BUTTON_MAZE:

									selected_button = BUTTON_TYPE::BUTTON_MAZE;
									current_draw_type = DRAW_TYPE::DRAW_MAZE;
									b.setSelected(true);
									DrawButtons(renderer, buttons);
									SDL_RenderPresent(renderer);
									break;
								
								case BUTTON_TYPE::BUTTON_ADD_WALLS:
									
									DrawButtonForAMoment(renderer, b);
									maze_generator.generate();
									
									start_already_drawn = false;
									finish_already_drawn = false;

									break;
								
								case BUTTON_TYPE::BUTTON_RESET:
								
									DrawButtonForAMoment(renderer, b);

									SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

									SDL_RenderClear(renderer);
									
									UnselectButton(selected_button, buttons);

									selected_button = BUTTON_TYPE::BUTTON_MAZE;
									current_draw_type = DRAW_TYPE::DRAW_MAZE;
									buttons.at(3).setSelected(true);
									DrawButtons(renderer, buttons);

									board.ClearBoard();
									search_algorithm_implementation->ClearBoard();

									for (Button& b : buttons) {
										b.setSelected(false);
									}

									// Instead of having booleans for these we could just check if the boards stored finish & start positions are -1, -1
									finish_already_drawn = false;
									start_already_drawn = false;
									break;
							}
						}
					}

				}

			}
			break;
	
		default:
			break;
		}

	}
}

int WinMain() {

	GameLoop();

	
	return 0;
}