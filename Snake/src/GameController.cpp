#include "GameController.h"
#include "GameBoard.h"

GameController::~GameController() 
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

GameController::GameController() :
	game_board_object(std::make_unique<GameBoard>()),
	window(),
	renderer()
{

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(screen_width_pixels, 
								screen_height_pixels, 
								NULL,
								&window,
								&renderer);

	SDL_SetWindowFullscreen(window, true);


	game_board_object.get()->DrawInitialBoard(renderer, screen_width_pixels / number_cells, screen_height_pixels / number_cells);
	SDL_RenderPresent(renderer);
}


void GameController::StartSnakeGame() 
{
		
	GameLoop();

}


void GameController::GameLoop() 
{

	bool continue_running_program = true;
	SDL_Event event;

	while (continue_running_program) {

		SDL_PollEvent(&event);

		switch (event.type) {

			case SDL_KEYDOWN: 
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					continue_running_program = false;

				break;
			}

			case SDL_QUIT: 
			{
				continue_running_program = SDL_FALSE;
				break;
			}

			case SDL_MOUSEBUTTONDOWN: 
			{
				if (event.button.button == SDL_BUTTON_LEFT);
			}

			default:
			{
				break;
			}
		}
	}
}


