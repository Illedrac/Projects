#pragma once
#include "SDL.h"
#include <memory>

const int screen_width = 1920;
const int screen_height = 1080;

const int FPS = 60;
const double frame_delay = 1e3 / FPS;
const double update_delay_normal = frame_delay * 25.0;
const double update_delay_fast = frame_delay * 3.0;

class GameBoard;
class Block;

class GameController 
{

public:
    GameController();

    ~GameController();

    void StartGame();
    void GameLoop();

private:

    SDL_Renderer* renderer;
    SDL_Window* window;

    std::unique_ptr<GameBoard> game_board_pointer;
    std::unique_ptr<Block> current_block_being_placed;
    std::unique_ptr<Block> next_block_to_be_placed;

    bool should_spawn_another_block;


};