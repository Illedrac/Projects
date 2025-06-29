#include "SDL.h"
#include "Minesweeper.h"


int WinMain()
{
    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_CreateWindowAndRenderer(Minesweeper::xResolution,
                                Minesweeper::yResolution, 
                                NULL, 
                                &window, 
                                &renderer);

    return 0;
}