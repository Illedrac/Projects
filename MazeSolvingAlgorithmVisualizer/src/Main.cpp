#include "SDL.h"
#include "SDL_image.h"
#include "MazeSolvingAlgorithmVisualizer.h"

int WinMain() {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);

	MazeSolvingAlgorithmVisualizer MSAV;

	MSAV.GameLoop();


	return 0;
}