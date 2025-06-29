#include "SDL.h"
#include "GameManager.h"
#include "Minesweeper.h"

GameManager::GameManager() :
    renderer(),
    window(),
    mineSweeperPointer(std::make_unique<Minesweeper>()),
	continueRunningProgram(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::runApplication()
{
    initWindowAndRenderer();

    GameLoop();

}

void GameManager::initWindowAndRenderer()
{
    SDL_CreateWindowAndRenderer(xResolution,
                                yResolution,
                                NULL,
                                &window,
                                &renderer);
}

void GameManager::GameLoop()
{
	SDL_Event event;

	while (continueRunningProgram)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					/*game_board_object.get()->SetScreenInitialized(false);
					main_menu = true;
					is_paused = true;

					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);*/
					return;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.scancode == SDL_SCANCODE_UP)
				{
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
				}
				
				break;
			}

			case SDL_QUIT:
			{
				continueRunningProgram = false;
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
	}
}
