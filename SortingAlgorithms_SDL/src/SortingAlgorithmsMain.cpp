#include <iostream>
#undef main

#include "SortingAlgorithmsMain.h"

SortingAlgorithmsMain::SortingAlgorithmsMain(int width, int height) :
    window(nullptr),
    renderer(nullptr),
    sorting_algorithm_implementation()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}


void SortingAlgorithmsMain::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SortingAlgorithmsMain::DrawInitialArray() {
   
    sorting_algorithm_implementation->DrawCurrentArray(window, renderer);
    
    // swap and display buffer
    SDL_RenderPresent(renderer);
}

void SortingAlgorithmsMain::Initialize(AlgorithmType algorithm_type, int width) {
    //Error Check
    if (window == nullptr || renderer == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window or Renderer are Null", NULL);
    }

    sorting_algorithm_implementation = AlgorithmFactory::CreateAlgorithm(algorithm_type, width);
    
}

int WinMain() {

    int width = 1000;
    SortingAlgorithmsMain* sAM = new SortingAlgorithmsMain(width, width);
    sAM->Initialize(AlgorithmType::INSERTION_SORT, width);

    SDL_Event event;
    bool continue_running_program = SDL_TRUE;
    bool full_screen = false;
    bool display_initial_array = true;
     
    while (continue_running_program) {
        while (SDL_PollEvent(&event)) {
            if (display_initial_array) {
                sAM->DrawInitialArray();
                display_initial_array = false;
            }

            switch (event.type) {
            case SDL_QUIT:
                continue_running_program = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                    full_screen = !full_screen;
                    if (full_screen) {
                        SDL_SetWindowFullscreen(sAM->window, SDL_WINDOW_FULLSCREEN);
                    }
                    else {
                        SDL_SetWindowFullscreen(sAM->window, 0);
                    }
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    sAM->sorting_algorithm_implementation->SortArray(sAM->window, sAM->renderer);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    continue_running_program = SDL_FALSE;
                }
                break;
            default: break;
            }
        }

        
    }
    
    return 0;
}