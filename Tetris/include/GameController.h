#pragma once
#include "SDL.h"
#include <memory>

const int screen_width = 1920;
const int screen_height = 1080;

const int FPS = 60;
const int frame_delay = 1e3 / FPS;

class GameBoard;

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
    
};