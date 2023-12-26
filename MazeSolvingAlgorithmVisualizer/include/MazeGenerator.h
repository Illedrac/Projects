#pragma once
#include "stdint.h"
#include "GameBoard.h"
#include <queue>


class MazeGenerator 
{

public:
    MazeGenerator(GameBoard* gb);

    bool isValid(int row, int col);
    void addWallsToList(int row, int col, std::queue<std::pair<int, int>>& walls);
    //void recursiveBacktrack(int row, int col);
    void generate();

private:

    GameBoard* game_board;
    
    int rows;
    int cols;
};
