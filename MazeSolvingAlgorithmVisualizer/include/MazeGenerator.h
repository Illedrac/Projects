#pragma once
#include "stdint.h"
#include "GameBoard.h"
#include <queue>


class MazeGenerator 
{

public:

    MazeGenerator();

    MazeGenerator(GameBoard* gb);

    void generate();

private:

    GameBoard* game_board;
    
    int rows;
    int cols;
};
