#include "GameController.h"
#include "GameBoard.h"
#include "Block_Factory.h"

GameController::GameController() :
    renderer(),
    window(),
    game_board_pointer(std::make_unique<GameBoard>(screen_width, screen_height)),
    current_block_being_placed(std::unique_ptr<Block>(Block_Factory::getBlock())),
    next_block_to_be_placed(std::unique_ptr<Block>(Block_Factory::getBlock())),
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
    Uint32 last_game_update = SDL_GetTicks();
    int frame_time;

    SDL_Event sdl_event;

    bool continue_running_program = true;

    double update_delay = update_delay_normal;

    while (continue_running_program)
    {
        frame_start = SDL_GetTicks();

        Uint8* keystate = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));

        if (update_delay != update_delay_fast && keystate[SDL_SCANCODE_S])
        {
            update_delay = update_delay_fast;
        }
        else if (update_delay != update_delay_normal && !keystate[SDL_SCANCODE_S])
        {
            update_delay = update_delay_normal;
        }

        while(SDL_PollEvent(&sdl_event))
        {
            switch (sdl_event.type) 
            {

                case SDL_KEYDOWN:
                {
                    if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        continue_running_program = false;
                        break;
                    }
                    
                    if (sdl_event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                    {
                        game_board_pointer.get()->ResetGameBoard();
                        current_block_being_placed = std::unique_ptr<Block>(Block_Factory::getBlock());
                        break;
                    }
                    
                    if (sdl_event.key.keysym.scancode == SDL_SCANCODE_D)
                    {
                        if (game_board_pointer.get()->CanBlockMoveRight(current_block_being_placed.get()->GetBlockPositionVector()))
                        {
                            current_block_being_placed.get()->MoveRight();
                            game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                                                 current_block_being_placed.get()->GetBlockPositionVector(),
                                                                                 current_block_being_placed.get()->GetBlockPositionPreviousVector());
                        }
                    }
                    else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_A)
                    {
                        if (game_board_pointer.get()->CanBlockMoveLeft(current_block_being_placed.get()->GetBlockPositionVector()))
                        {
                            current_block_being_placed.get()->MoveLeft();
                            game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                                                 current_block_being_placed.get()->GetBlockPositionVector(),
                                                                                 current_block_being_placed.get()->GetBlockPositionPreviousVector());
                        }
                    }  
                    else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_Q)
                    {
                        if (game_board_pointer.get()->CanBlockRotateLeft(current_block_being_placed.get()->GetBlockPositionVector()))
                        {
                            current_block_being_placed.get()->RotateBlockLeft();
                            game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                                                 current_block_being_placed.get()->GetBlockPositionVector(),
                                                                                 current_block_being_placed.get()->GetBlockPositionPreviousVector());
                        }
                    }
                    else if (sdl_event.key.keysym.scancode == SDL_SCANCODE_E)
                    {
                        if (game_board_pointer.get()->CanBlockRotateRight(current_block_being_placed.get()->GetBlockPositionVector()))
                        {
                            current_block_being_placed.get()->RotateBlockRight();
                            game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                                                 current_block_being_placed.get()->GetBlockPositionVector(),
                                                                                 current_block_being_placed.get()->GetBlockPositionPreviousVector());
                        }
                    }
                }
            }
        }

        if (SDL_GetTicks() - last_game_update > update_delay)
        {
            if (game_board_pointer.get()->CanBlockMoveDown(current_block_being_placed.get()->GetBlockPositionVector()))
            {
                current_block_being_placed.get()->MoveDown();
            }
            else
            {
                current_block_being_placed = std::move(next_block_to_be_placed);
                current_block_being_placed = std::unique_ptr<Block>(Block_Factory::getBlock());

                game_board_pointer.get()->CheckIfClearRow();
            }       

            last_game_update = SDL_GetTicks();
        }

        game_board_pointer.get()->UpdateCurrentBlockPosition(current_block_being_placed.get()->GetBlockType(),
                                                             current_block_being_placed.get()->GetBlockPositionVector(),
                                                             current_block_being_placed.get()->GetBlockPositionPreviousVector());

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);

        game_board_pointer.get()->DrawGameBoard(renderer);

    }
}
