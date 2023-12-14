#include "SDL.h"
#include "GameBoard.h"
#include "BFS_Algorithm.h"

enum DRAW_TYPE {
	DRAW_MAZE,
	DRAW_START,
	DRAW_FINISH
};

void GameLoop() {
	SDL_Renderer* renderer;
	SDL_Window* window;

	int screen_width_px = 1910;
	int screen_height_px = 1050;
	int number_cells_width = 200;
	int number_cells_height = 200;


	SDL_CreateWindowAndRenderer(screen_width_px, screen_height_px, NULL, &window, &renderer);

	GameBoard board(window, renderer, number_cells_width, number_cells_height, screen_width_px - (int)(screen_width_px / number_cells_width), screen_height_px - (int)(0.75 * screen_height_px / number_cells_height));


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
				case SDL_SCANCODE_B:
					BFS.BeginSearch();
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
					board = * (new GameBoard(window, renderer, number_cells_width, number_cells_height, screen_width_px - 2, screen_height_px - 1));
					BFS = * (new BFS_Algorithm(&board));
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

					int row_index = (mouse_y - board.getLineBetweenCellsOffset()) / board.gameBoard.at(0).at(0).getCellHeight();
					int col_index = (mouse_x - board.getLineBetweenCellsOffset()) / board.gameBoard.at(0).at(0).getCellWidth();


					if (row_index < 0 || row_index >= board.getCellsHeight() || col_index < 0 || col_index >= board.getCellsWidth())
						break;

					bool initial_button_state = board.gameBoard.at(row_index).at(col_index).isCellAWall();


					if (current_draw_type == DRAW_MAZE) {

						while (true) {

							SDL_GetMouseState(&mouse_x, &mouse_y);

							mouse_y = std::max(mouse_y, 0);
							mouse_x = std::max(mouse_x, 0);

							mouse_y = std::min(mouse_y, board.getScreenHeight());
							mouse_x = std::min(mouse_x, board.getScreenWidth());

							row_index = (mouse_y - board.getLineBetweenCellsOffset()) / board.gameBoard.at(0).at(0).getCellHeight();
							col_index = (mouse_x - board.getLineBetweenCellsOffset()) / board.gameBoard.at(0).at(0).getCellWidth();

							row_index = std::min(row_index, board.getCellsHeight() - 1);
							col_index = std::min(col_index, board.getCellsWidth() - 1);

							if (board.gameBoard.at(row_index).at(col_index).isCellAWall() == initial_button_state) {

								board.gameBoard.at(row_index).at(col_index).flipCellIsAWall();

								board.update_made = true;

								board.DrawGameBoard();
							}

							SDL_PollEvent(&event);
							if (event.type == SDL_MOUSEBUTTONUP) break;
						}

					}
					else if (current_draw_type == DRAW_START) {
						if (!start_already_drawn) {
							board.gameBoard.at(row_index).at(col_index).flipCellStart();
							board.setStartPosition(row_index, col_index);

							start_already_drawn = true;

							board.update_made = true;

							board.DrawGameBoard();
						}
						else if (board.gameBoard.at(row_index).at(col_index).isCellStart()) {
							board.gameBoard.at(row_index).at(col_index).flipCellStart();
							board.setFinishPosition(row_index, col_index);

							start_already_drawn = false;

							board.update_made = true;

							board.DrawGameBoard();
						}
					}
					else if (current_draw_type == DRAW_FINISH) {
						if (!finish_already_drawn) {
							board.gameBoard.at(row_index).at(col_index).flipCellFinish();
							finish_already_drawn = true;
							board.setFinishPosition(row_index, col_index);
							board.update_made = true;

							board.DrawGameBoard();
						}
						else if (board.gameBoard.at(row_index).at(col_index).isCellFinish()) {
							board.gameBoard.at(row_index).at(col_index).flipCellFinish();

							finish_already_drawn = false;

							board.update_made = true;

							board.DrawGameBoard();
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