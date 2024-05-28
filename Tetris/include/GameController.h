#pragma once
#include "SDL.h"

const int screen_width = 1920;
const int screen_height = 1080;

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


};