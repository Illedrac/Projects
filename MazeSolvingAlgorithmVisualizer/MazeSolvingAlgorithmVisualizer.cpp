#include "SDL.h"
#include "GameBoard.h"
#include "Button.h"
#include "BFS_Algorithm.h"
#include "SDL_image.h"
#include <string>
#include <algorithm>

enum DRAW_TYPE {
	DRAW_MAZE,
	DRAW_START,
	DRAW_FINISH
};

void CreateButtons(SDL_Renderer* renderer, std::vector<Button>& buttons) {
	
	Button Search_button(renderer, "Search_button.JPG", SDL_GetBasePath(), 10, BUTTON_TYPE::BUTTON_SEARCH);
	Button Start_button(renderer, "Start_button.JPG", SDL_GetBasePath(), 120, BUTTON_TYPE::BUTTON_START);
	Button Finish_button(renderer, "Finish_button.JPG", SDL_GetBasePath(), 230, BUTTON_TYPE::BUTTON_FINISH);
	Button Maze_button(renderer, "Maze_button.JPG", SDL_GetBasePath(), 340, BUTTON_TYPE::BUTTON_MAZE);
	Button Add_Walls_button(renderer, "Add_Walls_button.JPG", SDL_GetBasePath(), 450, BUTTON_TYPE::BUTTON_ADD_WALLS);
	Button Reset_button(renderer, "Reset_button.JPG", SDL_GetBasePath(), 560, BUTTON_TYPE::BUTTON_RESET);

	buttons.push_back(Search_button);
	buttons.push_back(Start_button);
	buttons.push_back(Finish_button);
	buttons.push_back(Maze_button);
	buttons.push_back(Add_Walls_button);
	buttons.push_back(Reset_button);

}

void DrawButtons(SDL_Renderer* renderer, std::vector<Button>& buttons){
	
	for (Button b : buttons) {
		SDL_RenderCopy(renderer, b.getTexture(), NULL, &b.getRect());
	}
	
}

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
	
	CreateButtons(renderer, buttons);
	DrawButtons(renderer, buttons);

	GameBoard board(window, renderer, number_cells_width, number_cells_height, screen_width_px - 160, screen_height_px - 50);


	bool continue_running_program = SDL_TRUE;
	bool mouse_button_held = false;
	bool finish_already_drawn = false;
	bool start_already_drawn = false;


	SDL_Event event;
	
	DRAW_TYPE current_draw_type = DRAW_MAZE;

	int mouse_x, mouse_y;

	BFS_Algorithm BFS(&board);

	while (continue_running_program) {
		board.DrawGameBoard();
		SDL_PollEvent(&event);

		switch (event.type) {

		case SDL_KEYDOWN:
	
			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					continue_running_program = false;
					break;
				case SDL_SCANCODE_B:
					continue_running_program = BFS.BeginSearch();
					break;
				case SDL_SCANCODE_F:
					current_draw_type = DRAW_FINISH;
					break;
				case SDL_SCANCODE_M:
					current_draw_type = DRAW_MAZE;
					break;
				case SDL_SCANCODE_S:
					current_draw_type = DRAW_START;
					break;
				case SDL_SCANCODE_R:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderClear(renderer);
					DrawButtons(renderer, buttons);
					board.ClearBoard();
					BFS.ClearBoard();
					
					// Instead of having booleans for these we could just check if the boards stored finish & start positions are -1, -1
					finish_already_drawn = false;
					start_already_drawn = false;
					break;
				case SDL_SCANCODE_G:
					board.generateUniformRandNoise();
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
						// Start isn't drawn so draw it
						if (!start_already_drawn) {
							board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::START;
							board.setStartPosition(row_index, col_index);

							start_already_drawn = true;

							board.update_made = true;

							board.DrawGameBoard();
						}
						// Start is drawn so unset current start
						else if (board.gameBoard.at(row_index).at(col_index) == CELL_TYPE::START) {
							board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
							board.setStartPosition(-1, -1);

							start_already_drawn = false;

							board.update_made = true;

							board.DrawGameBoard();
						}
					}
					else if (current_draw_type == DRAW_FINISH) {
						// Finish isn't drawn so draw it
						if (!finish_already_drawn) {
							
							board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::FINISH;
							board.setFinishPosition(row_index, col_index);

							finish_already_drawn = true;

							board.update_made = true;

							board.DrawGameBoard();
						}
						// Finish is drawn so unset current start
						else if (board.gameBoard.at(row_index).at(col_index) == CELL_TYPE::FINISH) {
							
							board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
							board.setFinishPosition(-1, -1);

							finish_already_drawn = false;

							board.update_made = true;

							board.DrawGameBoard();
						}
					}
				}
				

				else {
					for (Button& b : buttons) {
						SDL_Rect& rect = b.getRect();

						if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w) && mouse_y >= rect.y && mouse_y <= (rect.y + rect.h)) {
							switch (b.getButtonType()) {
								case BUTTON_TYPE::BUTTON_SEARCH:
									continue_running_program = BFS.BeginSearch();
									break;
								case BUTTON_TYPE::BUTTON_START:
									current_draw_type = DRAW_TYPE::DRAW_START;
									break;
								case BUTTON_TYPE::BUTTON_FINISH:
									current_draw_type = DRAW_TYPE::DRAW_FINISH;
									break;
								case BUTTON_TYPE::BUTTON_MAZE:
									current_draw_type = DRAW_TYPE::DRAW_MAZE;
									break;
								case BUTTON_TYPE::BUTTON_ADD_WALLS:
									board.generateUniformRandNoise();
									break;
								case BUTTON_TYPE::BUTTON_RESET:
									SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
									SDL_RenderClear(renderer);
									DrawButtons(renderer, buttons);
									board.ClearBoard();
									BFS.ClearBoard();

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