#pragma once 
#include <random>
#include <unordered_set>
#include "SDL.h"

// Enum for determining which algorithm implemenatation should be used
enum AlgorithmType {
    INSERTION_SORT,
    BINARY_INSERTION_SORT,
    SELECTION_SORT,
    QUICK_SORT
};


// This is an abstract class that all sorting algorithm implementations are children of
// It includes some functions that are common to all algorithm implementations so they're defined here
class Algorithm {
public:
    // Virtual function to be implemented by each sorting algorithm
    virtual bool SortArray(SDL_Window* window, SDL_Renderer* renderer) = 0;
    
    // A function to "return control" back to SDL and make sure the sorting algorithm doesn't stop the user from
    // closing, moving the window, etc
    bool CheckSDLEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_WINDOWEVENT_MOVED:
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    return false;
                break;
            case SDL_QUIT:
                return false;
                break;

            default:
                break;
            }
        }
        return true;
    }


    // A function to draw the entire array  
    void DrawInitialArray(SDL_Window* window, SDL_Renderer* renderer, int screen_width) {
        for (int i = 0; i < unsortedNumbersArray->size(); i++) {
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width);
        }
        SDL_RenderPresent(renderer);
    }

    // A function to draw a rectangle to screen at a given x position and color
    void DrawCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX, int screen_width) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect;
        rect.x = posX * (screen_width / unsortedNumbersArray->size());
        rect.y = screen_width - (unsortedNumbersArray->at(posX) * (screen_width / unsortedNumbersArray->size()));
        rect.w = screen_width / unsortedNumbersArray->size();
        rect.h = unsortedNumbersArray->at(posX) * (screen_width / unsortedNumbersArray->size());
        SDL_RenderFillRect(renderer, &rect);
    }
    
    // A function to draw the entire array  
    void DrawCurrentArray(SDL_Window* window, SDL_Renderer* renderer, int screen_width) {
        for (int i = 0; i < unsortedNumbersArray->size(); i++) {
            ClearCurrentArrayAtIndex(window, renderer, i, screen_width);
            DrawCurrentArrayAtIndex(window, renderer, i, screen_width);
        }
        SDL_RenderPresent(renderer);
    }

    // A function to draw a rectangle to screen at a given x position and color
    void DrawCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX, int screen_width, SDL_Color color){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect;
        rect.x = posX * (screen_width / unsortedNumbersArray->size());
        rect.y = screen_width - (unsortedNumbersArray->at(posX) * (screen_width / unsortedNumbersArray->size()));
        rect.w = screen_width / unsortedNumbersArray->size();
        rect.h = unsortedNumbersArray->at(posX) * (screen_width / unsortedNumbersArray->size());
        SDL_RenderFillRect(renderer, &rect);
    }

    // A function that draws a black rectangle at a given x from y 0 : screen_width
    void ClearCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX, int screen_width) {
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_Rect rect;
        rect.x = posX * (screen_width / unsortedNumbersArray->size());
        rect.y = 0;
        rect.w = screen_width / unsortedNumbersArray->size();
        rect.h = screen_width;
        SDL_RenderFillRect(renderer, &rect);
    }

    // Create an unsorted array of size screen_width
    void CreateUnsortedArray(int  screen_width) {
        
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1,  screen_width);
        
        unsortedNumbersArray = new std::vector<int>;

        unsortedNumbersSet.clear();
        
        //GenerateRGB( screen_width);

        
        while (unsortedNumbersSet.size() <  screen_width) {
            int curNum = distrib(gen);

            if (unsortedNumbersSet.find(curNum) == unsortedNumbersSet.end()) {
                unsortedNumbersSet.insert(curNum);
                unsortedNumbersArray->push_back(curNum);
            }
        }
    }

    // A function to generate rgb values to give a spectrum (not working at the moment)
    void GenerateRGB(int  screen_width) {
        int r = 255;
        int g = 5;
        int b = 5;

        for (int i = 0; i <  screen_width; i++) {
            if (i >= 0 && i <= ( screen_width / 4)) {
                g += 2;
                if (g > 255) g = 255;
            }
            else if (i > ( screen_width / 4) && i < ( screen_width / 2)) {
                r -= 2;
                if (r < 1) r = 1;
            }
            else if (i > ( screen_width / 2) && i < (3 *  screen_width / 4)) {
                b += 2;
                if (b > 255) b = 255;
            }
            else {
                g -= 2;
                if (g < 1) g = 1;
            }
            //std::cout << "I: " << i << " R: " << r << " G: " << g << " B: " << b << std::endl;

            ArrayColors.push_back(std::make_tuple(r, g, b));
        }
    }

    // Using a set since we don't have to check if a random value is already in the set
    std::unordered_set<int> unsortedNumbersSet;
    // An unused vector to store rgb values 
    std::vector<std::tuple<int, int, int>> ArrayColors;
    // A vector to store the actual unsorted numbers (used to be an array, need to refactor)
    std::vector<int>* unsortedNumbersArray;
    // A boolean to store whether the sorting algorithm has finished sorting
    bool isSorted = false;
};
