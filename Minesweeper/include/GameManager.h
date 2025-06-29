#pragma once
#include <memory>

class Minesweeper;

struct SDL_Renderer;
struct SDL_Window;

class GameManager
{
public:
    
    GameManager();
    ~GameManager();

    void runApplication();
    void initWindowAndRenderer();
    void GameLoop();

private:

    SDL_Renderer* renderer;
    SDL_Window* window;

    std::unique_ptr<Minesweeper> mineSweeperPointer;

    bool continueRunningProgram;

    const int xResolution = 1920;
    const int yResolution = 1080;


};