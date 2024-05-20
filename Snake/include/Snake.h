#pragma once
#include "vector"
#include "utility"
#include <memory>
#include <queue>
#include "SDL.h"

enum DIRECTION {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GameBoard;

class Snake {

public:

    Snake();

    void Reset(std::shared_ptr<GameBoard> game_board_ptr);

    inline void addMoveToQueue(DIRECTION next_dir) { move_queue.push(next_dir); }

    void InitSnake(std::shared_ptr<GameBoard> game_board_ptr);

    bool UpdateSnakeLocation(std::shared_ptr<GameBoard> game_board_ptr, 
                             SDL_Renderer* renderer);
    
    inline int GetScore() { return score; }
private:

    bool MoveSnakeGivenDirection(std::shared_ptr<GameBoard> game_board_ptr, 
                                 DIRECTION next_direction);

    bool CanITurnThisDirection(DIRECTION next_direction);

    std::vector<std::pair<int, int>> snake_body_indexes;

    std::queue<DIRECTION> move_queue;
    DIRECTION prev_direction;
    bool hit_wall_once;
    int score;
};