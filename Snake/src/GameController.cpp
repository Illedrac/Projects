#include "GameController.h"
#include "GameBoard.h"
#include "FoodHandler.h"
#include "Snake.h"
#include "ButtonHandler.h"
#include "ScoreBoard.h"

GameController::~GameController() 
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

GameController::GameController() :
	game_board_object(std::make_shared<GameBoard>(screen_width_pixels, screen_height_pixels)),
	snake_object(std::make_unique<Snake>()),
	button_handler(nullptr),
	score_board(std::make_unique<ScoreBoard>(GetFontPath("November"))),
	window(),
	renderer(),
	frame_start(),
	frame_time(),
	last_update_made(SDL_GetTicks()),
	continue_running_program(true),
	main_menu(true),
	is_paused(false),
	game_over(false),
	event()
{

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(screen_width_pixels, 
								screen_height_pixels, 
								NULL,
								&window,
								&renderer);

	snake_object->InitSnake(game_board_object);

	button_handler = std::make_unique<ButtonHandler>(renderer);
	
}

void GameController::StartSnakeGame() 
{
	
	GameLoop();
}


void GameController::GameLoop() 
{

	while (continue_running_program) 
	{

		frame_start = SDL_GetTicks();

		if (main_menu)
		{
			DisplayMainMenu();
		}
		else if (game_over)
		{
			GameOver();
		}
		else
		{
			DisplayGame();
		}

		
	}

	frame_time = SDL_GetTicks() - frame_start;

	if (frame_delay > frame_time) {

		SDL_Delay(frame_delay - frame_time);

	}

}


void GameController::DisplayMainMenu()
{
	button_handler.get()->DrawButtons(renderer, is_paused);
	
	int mouse_x;
	int mouse_y;
	
	while (SDL_PollEvent(&event) != 0)
	{
	
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				if (!is_paused)
				{
					continue_running_program = false;

				}
				else
				{
					main_menu = false;
					is_paused = false;
				}

				if (game_over)
				{
					DisplayGameOver();
				}
			}
			break;
		}

		case SDL_QUIT:
		{
			continue_running_program = SDL_FALSE;
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&mouse_x, &mouse_y);

				for (int i = 0; i < button_handler.get()->GetButtonVectorSize(); i++) {

					SDL_Rect& rect = button_handler.get()->GetButtonVector().at(i).get()->getRect();

					if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w) && mouse_y >= rect.y && mouse_y <= (rect.y + rect.h))
					{
						switch (button_handler.get()->GetButtonVector().at(i).get()->getButtonType())
						{
							case BUTTON_LOGO:
							{
								break;
							}
							case BUTTON_PLAY:
							{
								main_menu = false;
								return;
							}
							case BUTTON_QUIT :
							{
								continue_running_program = false;
								return;
							}
						}
					}
				}
			}
		}

		case SDL_MOUSEMOTION:
		{
			SDL_GetMouseState(&mouse_x, &mouse_y);

			for (int i = 0; i < button_handler.get()->GetButtonVectorSize(); i++) {

				SDL_Rect& rect = button_handler.get()->GetButtonVector().at(i).get()->getRect();

				if (mouse_x >= rect.x && mouse_x <= (rect.x + rect.w) && mouse_y >= rect.y && mouse_y <= (rect.y + rect.h)) 
				{

					button_handler.get()->GetButtonVector().at(i).get()->setSelected(true);
				}
				else
					button_handler.get()->GetButtonVector().at(i).get()->setSelected(false);

			}

		}

		default:
		{
			break;
		}
		}
	}

}

void GameController::DisplayGame()
{
	if(!game_board_object.get()->IsScreenInitialized())
		game_board_object.get()->InitScreenToPlayGame(renderer);


	score_board.get()->DisplayScore(renderer, snake_object.get()->GetScore());


	if (!game_board_object.get()->getFoodExist())
	{
		FoodHandler::SpawnFood(game_board_object);
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				game_board_object.get()->SetScreenInitialized(false);
				main_menu = true;
				is_paused = true;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP)
				snake_object.get()->addMoveToQueue(UP);

			else if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				snake_object.get()->addMoveToQueue(LEFT);

			else if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				snake_object.get()->addMoveToQueue(DOWN);

			else if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
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
			if (event.button.button == SDL_BUTTON_LEFT)
			{

			}
		}

		default:
		{
			break;
		}
		}
	}



	if (SDL_GetTicks() - last_update_made > snake_update_delay_ms)
	{
		if (!game_over && snake_object.get()->UpdateSnakeLocation(game_board_object, renderer))
			game_board_object.get()->DrawBoard(renderer);
		else
		{
			game_over = true;
			DisplayGameOver();
			return;
		}


		last_update_made = SDL_GetTicks();
	}

	
}

void GameController::GameOver()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				continue_running_program = false;
				return;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_R && game_over)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);

				game_board_object.get()->SetScreenInitialized(false);

				game_over = false;

				game_board_object.get()->Reset();

				snake_object.get()->Reset(game_board_object);

				score_board.get()->DisplayScore(renderer, snake_object.get()->GetScore());
			}
		}
		}
	}
}


void GameController::DisplayGameOver()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	score_board.get()->DisplayGameOver(renderer, 
									   snake_object.get()->GetScore(),
									   screen_width_pixels, 
									   screen_height_pixels);

	
}

std::string GameController::GetFontPath(const std::string& font_name) {
	
	std::string path_to_font = SDL_GetBasePath();
	
	path_to_font = path_to_font.substr(2, path_to_font.size() - 1);
	
	std::replace(path_to_font.begin(), path_to_font.end(), '\\', '/');
	
	path_to_font.append("../Resources/");
	
	path_to_font.append(font_name);

	return path_to_font;
}