#include "GameController.h"
#include "GameBoard.h"

GameController::GameController() :
    renderer(),
    window(),
    game_board_pointer(std::make_unique<GameBoard>(screen_width, screen_height))
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(screen_width, screen_height, NULL, &window, &renderer);

}

GameController::~GameController()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void GameController::StartGame()
{
    GameLoop();

}

void GameController::GameLoop()
{
    SDL_Event sdl_event;

    bool continue_running_program = true;

    while (continue_running_program)
    {

        SDL_PollEvent(&sdl_event);

        switch (sdl_event.type) 
        {

            case SDL_KEYDOWN:
            {
                if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    continue_running_program = false;
                    break;
                }
            }

        }

        game_board_pointer.get()->DrawGameBoard(renderer);

    }
}
