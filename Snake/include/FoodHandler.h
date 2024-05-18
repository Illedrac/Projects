#pragma once
#include "memory"
#include "SDL.h"

class GameBoard;

class FoodHandler {


public:

    static bool SpawnFood(std::shared_ptr<GameBoard> g);

};