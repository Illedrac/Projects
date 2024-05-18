#include "GameController.h"
#include "GameBoard.h"
#include "FoodHandler.h"
#include "Snake.h"

GameController::~GameController() 
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

GameController::GameController() :
	game_board_object(std::make_shared<GameBoard>(screen_width_pixels / number_cells, screen_height_pixels / number_cells)),
	snake_object(std::make_unique<Snake>()),
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


	game_board_object.get()->DrawBoard(renderer);
	SDL_RenderPresent(renderer);
}


void GameController::StartSnakeGame() 
{
		
	GameLoop();

}


void GameController::GameLoop() 
{

	const int FPS = 60;
	const int frame_delay = 1000 / FPS;

	// More variables to control frame rate
	Uint32 frame_start;
	int frame_time;
	int last_update_made = SDL_GetTicks();

	bool continue_running_program = true;
	SDL_Event event;

	snake_object->InitSnake(game_board_object);
	game_board_object.get()->DrawBoard(renderer);

	while (continue_running_program) 
	{

		frame_start = SDL_GetTicks();

		if (!game_board_object.get()->getFoodExist())
		{
			FoodHandler::SpawnFood(game_board_object);
		}

		while(SDL_PollEvent(&event) != 0)
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN: 
				{
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						continue_running_program = false;
				

					if (event.key.keysym.scancode == SDL_SCANCODE_W)
						snake_object.get()->addMoveToQueue(UP);
					
					else if (event.key.keysym.scancode == SDL_SCANCODE_A)
						snake_object.get()->addMoveToQueue(LEFT);
				
					else if (event.key.keysym.scancode == SDL_SCANCODE_S)
						snake_object.get()->addMoveToQueue(DOWN);
				
					else if (event.key.keysym.scancode == SDL_SCANCODE_D)
						snake_object.get()->addMoveToQueue(RIGHT);

					break;
				}

				case SDL_QUIT: 
				{
					continue_running_program = SDL_FALSE;
					break;
				}

				case SDL_MOUSEBUTTONDOWN: 
				{
					if(event.button.button == SDL_BUTTON_LEFT) {
						// Going to need to update how this works
						if (!FoodHandler::SpawnFood(game_board_object)) 
							break;
					
						game_board_object.get()->DrawBoard(renderer);
						SDL_RenderPresent(renderer);
					}
				}

				default:
				{
					break;
				}
			}
		}


		
		if (SDL_GetTicks() - last_update_made > 70)
		{
			if (snake_object.get()->UpdateSnakeLocation(game_board_object, renderer))
				game_board_object.get()->DrawBoard(renderer);
			else
			{
				game_board_object.get()->Reset();
				snake_object.get()->Reset(game_board_object);
			}
				

			last_update_made = SDL_GetTicks();
		}
		
		
		frame_time = SDL_GetTicks() - frame_start;


		if (frame_delay > frame_time) {
		
			SDL_Delay(frame_delay - frame_time);
			
		}
	}
}

