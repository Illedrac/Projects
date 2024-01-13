#include <string>
#include <algorithm>
#include "MazeSolvingAlgorithmVisualizer.h"
#include "SDL.h"
#include "SDL_image.h"



MazeSolvingAlgorithmVisualizer::MazeSolvingAlgorithmVisualizer()
	:
	window(SDL_CreateWindow("Maze Solving Algorithm Visualizer", 5, 5, screen_width_px, screen_height_px, NULL)),
	renderer(SDL_CreateRenderer(window, 0, NULL)),
	button_container(renderer),
	board(window, renderer, number_cells_width, number_cells_height, screen_width_px - 160, screen_height_px - 50),
	maze_generator(&board),
	searchType(SEARCH_ALGORITHM_TYPE::BFS),
	factory(&board),
	search_algorithm_implementation(factory.CreateAlgorithmImplementation(searchType))

{
}

// This really needs to be cleaned up 
void MazeSolvingAlgorithmVisualizer::GameLoop() {
	
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

			case SDL_KEYDOWN: {
	
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_D:{
						if (searchType != SEARCH_ALGORITHM_TYPE::DFS) {

							BUTTON_TYPE this_should_be_fixed = BUTTON_TYPE::BUTTON_BFS;
							button_container.ButtonPressed(renderer, this_should_be_fixed, BUTTON_TYPE::BUTTON_DFS);
							searchType = SEARCH_ALGORITHM_TYPE::DFS;
							search_algorithm_implementation = factory.CreateAlgorithmImplementation(searchType);
						
						}

						break;
					}

					case SDL_SCANCODE_B: {

						if (searchType != SEARCH_ALGORITHM_TYPE::BFS) {

							BUTTON_TYPE this_should_be_fixed = BUTTON_TYPE::BUTTON_DFS;
							button_container.ButtonPressed(renderer, this_should_be_fixed, BUTTON_TYPE::BUTTON_BFS);
							searchType = SEARCH_ALGORITHM_TYPE::BFS;
							search_algorithm_implementation = factory.CreateAlgorithmImplementation(searchType);

						}

						break;
					}

					case SDL_SCANCODE_ESCAPE:
					
						continue_running_program = false;
						break;

					case SDL_SCANCODE_E:

						button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_SEARCH);

						if (board.readyToStartSearch())
							continue_running_program = search_algorithm_implementation->BeginSearch();

						break;
				
					case SDL_SCANCODE_F:

						button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_FINISH);
						current_draw_type = DRAW_TYPE::DRAW_FINISH;
						break;
				
					case SDL_SCANCODE_M:

						button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_MAZE);
						current_draw_type = DRAW_TYPE::DRAW_MAZE;
						break;
				
					case SDL_SCANCODE_S:

						button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_START);
						current_draw_type = DRAW_TYPE::DRAW_START;
						break;
				
					case SDL_SCANCODE_R:
				
						button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_RESET);

						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

						SDL_RenderClear(renderer);

						button_container.ClearButtons(renderer, selected_button);

						// I should replace DRAW_TYPE with BUTTON_TYPE
						current_draw_type = DRAW_TYPE::DRAW_MAZE;

						board.ClearBoard();
						search_algorithm_implementation->ClearBoard();

						// Instead of having booleans for these we could just check if the boards stored finish & start positions are -1, -1
						finish_already_drawn = false;
						start_already_drawn = false;
						break;

					case SDL_SCANCODE_G:
					
						button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_ADD_WALLS);

						maze_generator.generate();

						start_already_drawn = false;
						finish_already_drawn = false;

						board.setStartPosition(-1, -1);
						board.setFinishPosition(-1, -1);
						break;

					default:
						break;
				}

				break;
			}

			case SDL_QUIT: {
				continue_running_program = SDL_FALSE;
				break;
			}

			case SDL_MOUSEBUTTONDOWN: {
				if (event.button.button == SDL_BUTTON_LEFT) {

					SDL_GetMouseState(&mouse_x, &mouse_y);

					// If the click is on the GameBoard
					if (mouse_x >= 0 && mouse_x < board.getScreenWidth() && mouse_y >= 0 && mouse_y < board.getScreenHeight()) {

						mouse_y = std::max(mouse_y, 0);
						mouse_x = std::max(mouse_x, 0);

						mouse_y = std::min(mouse_y, board.getScreenHeight());
						mouse_x = std::min(mouse_x, board.getScreenWidth());

						int row_index = (mouse_y - board.getLineBetweenCellsOffset()) / board.getCellHeightPx();
						int col_index = (mouse_x - board.getLineBetweenCellsOffset()) / board.getCellWidthPx();


						if (row_index < 0 || row_index >= board.getCellsHeight() || col_index < 0 || col_index >= board.getCellsWidth())
							break;

						CELL_TYPE initial_button_state = board.gameBoard.at(row_index).at(col_index);


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

								CELL_TYPE current_cell_type = board.gameBoard.at(row_index).at(col_index);

								if (current_cell_type == initial_button_state) {

									if (current_cell_type == CELL_TYPE::WALL) {
										board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
									}
									else if (current_cell_type == CELL_TYPE::NORMAL_PATH) {
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

							if (board.getFinishRowPosition() == row_index && board.getFinishColPosition() == col_index)
								break;

							if (board.getStartRowPosition() == row_index && board.getStartColPosition() == col_index) {

								start_already_drawn = false;

								board.setStartPosition(-1, -1);

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
							}
							else if (board.getStartRowPosition() != -1 || board.getStartColPosition() != -1) {

								board.gameBoard.at(board.getStartRowPosition()).at(board.getStartColPosition()) = CELL_TYPE::NORMAL_PATH;

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::START;

								board.setStartPosition(row_index, col_index);

							}
							else {

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::START;

								board.setStartPosition(row_index, col_index);

								start_already_drawn = true;
							}

							board.update_made = true;

							board.DrawGameBoard();


						}
						else if (current_draw_type == DRAW_FINISH) {

							if (board.getStartRowPosition() == row_index && board.getStartColPosition() == col_index)
								break;

							if (board.getFinishRowPosition() == row_index && board.getFinishColPosition() == col_index) {

								finish_already_drawn = false;

								board.setFinishPosition(-1, -1);

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::NORMAL_PATH;
							}
							else if (board.getFinishRowPosition() != -1 || board.getFinishColPosition() != -1) {

								board.gameBoard.at(board.getFinishRowPosition()).at(board.getFinishColPosition()) = CELL_TYPE::NORMAL_PATH;

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::FINISH;

								board.setFinishPosition(row_index, col_index);

							}
							else {

								board.gameBoard.at(row_index).at(col_index) = CELL_TYPE::FINISH;

								board.setFinishPosition(row_index, col_index);

								start_already_drawn = true;
							}

							board.update_made = true;

							board.DrawGameBoard();
						}
					}

					// If the click is not on the GameBoard i.e the "menu"
					else {
						for (int i = 0; i < button_container.GetButtonVector().size(); i++) {

							Button b = button_container.GetButtonVector().at(i);

							SDL_Rect& rect = b.getRect();

							if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w) && mouse_y >= rect.y && mouse_y <= (rect.y + rect.h)) {

								switch (b.getButtonType()) {
									case BUTTON_TYPE::BUTTON_SEARCH:{

										button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_SEARCH);

										if (board.readyToStartSearch())
											continue_running_program = search_algorithm_implementation->BeginSearch();
										
										button_container.UnselectButton(selected_button);
										
										break;
									}

									case BUTTON_TYPE::BUTTON_START: {

										button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_START);
										current_draw_type = DRAW_TYPE::DRAW_START;

										button_container.UnselectButton(selected_button);

										break;
									}

									case BUTTON_TYPE::BUTTON_FINISH: {

										button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_FINISH);
										current_draw_type = DRAW_TYPE::DRAW_FINISH;

										button_container.UnselectButton(selected_button);

										break;
									}

									case BUTTON_TYPE::BUTTON_MAZE: {

										button_container.ButtonPressed(renderer, selected_button, BUTTON_TYPE::BUTTON_MAZE);
										current_draw_type = DRAW_TYPE::DRAW_MAZE;

										button_container.UnselectButton(selected_button);

										break;
									}

									case BUTTON_TYPE::BUTTON_ADD_WALLS: {

										button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_ADD_WALLS);

										maze_generator.generate();

										start_already_drawn = false;
										finish_already_drawn = false;

										board.setStartPosition(-1, -1);
										board.setFinishPosition(-1, -1);

										button_container.UnselectButton(selected_button);

										break;
									}

									case BUTTON_TYPE::BUTTON_RESET: {

										button_container.DrawButtonForAMoment(renderer, BUTTON_TYPE::BUTTON_RESET);

										SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

										SDL_RenderClear(renderer);

										button_container.ClearButtons(renderer, selected_button);

										// I should replace DRAW_TYPE with BUTTON_TYPE
										current_draw_type = DRAW_TYPE::DRAW_MAZE;

										board.ClearBoard();
										search_algorithm_implementation->ClearBoard();

										// Instead of having booleans for these we could just check if the boards stored finish & start positions are -1, -1
										finish_already_drawn = false;
										start_already_drawn = false;

										button_container.UnselectButton(selected_button);

										break;
									}

									case BUTTON_TYPE::BUTTON_DFS: {

										if (searchType != SEARCH_ALGORITHM_TYPE::DFS) {

											BUTTON_TYPE this_should_be_fixed = BUTTON_TYPE::BUTTON_BFS;
											button_container.ButtonPressed(renderer, this_should_be_fixed, BUTTON_TYPE::BUTTON_DFS);
											searchType = SEARCH_ALGORITHM_TYPE::DFS;
											search_algorithm_implementation = factory.CreateAlgorithmImplementation(searchType);

										}

										break;
									}

									case BUTTON_TYPE::BUTTON_BFS: {

										if (searchType != SEARCH_ALGORITHM_TYPE::BFS) {

											BUTTON_TYPE this_should_be_fixed = BUTTON_TYPE::BUTTON_DFS;
											button_container.ButtonPressed(renderer, this_should_be_fixed, BUTTON_TYPE::BUTTON_BFS);
											searchType = SEARCH_ALGORITHM_TYPE::BFS;
											search_algorithm_implementation = factory.CreateAlgorithmImplementation(searchType);

										}

										break;
									}

									default:
										break;
								}
							}
						}

					}

				}
				break;
			}

			default:
				break;
		}

	}
}

