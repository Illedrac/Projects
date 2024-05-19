#pragma once
#include <memory>
#include <SDL.h>

class GameBoard;
class Snake;

const int screen_width_pixels = 1920;
const int screen_height_pixels = 1080;
const int snake_update_delay_ms = 65;


class GameController {

public:

    GameController();
    ~GameController();

    void StartSnakeGame();
    void GameLoop();

private:

    std::shared_ptr<GameBoard> game_board_object;
    std::unique_ptr<Snake> snake_object;
    
    // I would've liked these to be unique_ptrs but these
    // don't have deconstructors so unique_ptrs not only don't work
    // but wouldn't actually clean the memory
    SDL_Window* window;
    SDL_Renderer* renderer;


};