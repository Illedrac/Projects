#pragma once 
#include <random>
#include <unordered_set>
#include "SDL.h"

enum AlgorithmType {
    INSERTION_SORT,
    BUBBLE_SORT
};

class Algorithm {
public:
    virtual void SortArray(SDL_Window* window, SDL_Renderer* renderer) = 0;
    virtual void DrawCurrentArray(SDL_Window* window, SDL_Renderer* renderer) = 0;
    virtual void DrawCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX) = 0;
    virtual void ClearCurrentArrayAtIndex(SDL_Window* window, SDL_Renderer* renderer, int posX) = 0;

    inline void CreateUnsortedArray(int SCREEN_WIDTH_HEIGHT) {
        
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, SCREEN_WIDTH_HEIGHT);
        
        unsortedNumbersArray = new std::vector<int>;

        unsortedNumbersSet.clear();
        
        //GenerateRGB(SCREEN_WIDTH_HEIGHT);

        
        while (unsortedNumbersSet.size() < SCREEN_WIDTH_HEIGHT) {
            int curNum = distrib(gen);

            if (unsortedNumbersSet.find(curNum) == unsortedNumbersSet.end()) {
                unsortedNumbersSet.insert(curNum);
                unsortedNumbersArray->push_back(curNum);
            }
        }
    }

    inline void GenerateRGB(int SCREEN_WIDTH_HEIGHT) {
        int r = 255;
        int g = 5;
        int b = 5;

        for (int i = 0; i < SCREEN_WIDTH_HEIGHT; i++) {
            if (i >= 0 && i <= (SCREEN_WIDTH_HEIGHT / 4)) {
                g += 2;
                if (g > 255) g = 255;
            }
            else if (i > (SCREEN_WIDTH_HEIGHT / 4) && i < (SCREEN_WIDTH_HEIGHT / 2)) {
                r -= 2;
                if (r < 1) r = 1;
            }
            else if (i > (SCREEN_WIDTH_HEIGHT / 2) && i < (3 * SCREEN_WIDTH_HEIGHT / 4)) {
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

    std::unordered_set<int> unsortedNumbersSet;
    std::vector<std::tuple<int, int, int>> ArrayColors;
    std::vector<int>* unsortedNumbersArray;
    bool isSorted = false;
};
