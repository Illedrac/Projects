#include "GameController.h"
#include "GameBoard.h"
#include "Block_Factory.h"

GameController::GameController() :
    renderer(),
    window(),
    game_board_pointer(std::make_unique<GameBoard>(screen_width, screen_height)),
    current_block_being_placed(),
    should_spawn_another_block(true)

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
    Uint32 frame_start;
    int frame_time;

    SDL_Event sdl_event;

    bool continue_running_program = true;

    while (continue_running_program)
    {
        frame_start = SDL_GetTicks();

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

        if (should_spawn_another_block)
        {
            current_block_being_placed = std::unique_ptr<Block>(Block_Factory::getBlock(BLOCK_TYPE::O));
            should_spawn_another_block = false;

            game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                                 current_block_being_placed.get()->GetBlockPositionVector());
        }
        else
        {

        }

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);

        game_board_pointer.get()->DrawGameBoard(renderer);

    }
}
