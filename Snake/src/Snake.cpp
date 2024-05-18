#include "Snake.h"
#include "GameBoard.h"
#include "FoodHandler.h"

Snake::Snake() :
    snake_body_indexes(),
    move_queue(),
    prev_direction(NONE)
{
    snake_body_indexes.push_back(std::make_pair(15, 15));
    //This might be an issue later when resizing but using current_pair reference
}


void Snake::InitSnake(std::shared_ptr<GameBoard> game_board_ptr) 
{
    game_board_ptr.get()->setCellType(snake_body_indexes.at(0).first, snake_body_indexes.at(0).second, CELL_TYPE::SNAKE);
}

void Snake::Reset(std::shared_ptr<GameBoard> game_board_ptr)
{
    prev_direction = NONE;
    snake_body_indexes.clear();
    snake_body_indexes.push_back(std::make_pair(15, 15));
    game_board_ptr.get()->setCellType(15, 15, SNAKE);
}

bool Snake::UpdateSnakeLocation(std::shared_ptr<GameBoard> game_board_ptr, SDL_Renderer* renderer)
{
    // Don't do anything if waiting for first direction
    if (prev_direction != NONE || move_queue.size() > 0) 
    {
        if (move_queue.size() == 0)
        {
            return MoveSnakeGivenDirection(game_board_ptr, prev_direction);
        }
        
        
        while (move_queue.size() > 0)
        {
            DIRECTION next_direction = move_queue.front();
            move_queue.pop();

            bool can_turn_this_direction = false;

            if (prev_direction == NONE)
            {
                can_turn_this_direction = true;
            }
            else 
            {
                can_turn_this_direction = CanITurnThisDirection(next_direction);
            }

            // If you can't turn this direction, just continue going the way we already were
            if (!can_turn_this_direction)
            {
                MoveSnakeGivenDirection(game_board_ptr, prev_direction);
            }
            // If we can go this direction, move in that direction
            // If we enter in this if statement, the snake is out of bounds.
            else if(!MoveSnakeGivenDirection(game_board_ptr, next_direction))
            {
                game_board_ptr.get()->DrawBoard(renderer);
                return false;
            }
        }
    }

    return true;
}


bool Snake::MoveSnakeGivenDirection(std::shared_ptr<GameBoard> game_board_ptr, DIRECTION next_direction)
{
    std::pair<int, int> new_head_indexes(snake_body_indexes.at(0).first,
                                         snake_body_indexes.at(0).second);


    switch (next_direction) {
        case UP:
        {
            new_head_indexes.first -= 1;
            break;
        }
        case DOWN:
        {
            new_head_indexes.first += 1;
            break;
        }
        case LEFT:
        {
            new_head_indexes.second -= 1;
            break;
        }
        case RIGHT:
        {
            new_head_indexes.second += 1;
            break;
        }
        
        case NONE:
        default:
        {
            break;
        }
    }

    //Bounds Checking
    if (new_head_indexes.first < 0 ||
        new_head_indexes.first > game_board_ptr.get()->getMaxHeight()) return false;
    
    if (new_head_indexes.second < 0 ||
        new_head_indexes.second > game_board_ptr.get()->getMaxWidth()) return false;


    if (game_board_ptr.get()->getCellType(new_head_indexes.first, new_head_indexes.second) == SNAKE) return false;

    if (!game_board_ptr.get()->IsOnFood(new_head_indexes.first, new_head_indexes.second))
    {
        game_board_ptr.get()->setCellType(snake_body_indexes.at(snake_body_indexes.size() - 1).first,
                                          snake_body_indexes.at(snake_body_indexes.size() - 1).second,
                                          CELL_TYPE::EMPTY);

        snake_body_indexes.pop_back();
    }
    else 
    {
        
        game_board_ptr.get()->setFoodExist(false);
        game_board_ptr.get()->setFood(-1, -1);
    }

    snake_body_indexes.insert(snake_body_indexes.begin(), new_head_indexes);

    game_board_ptr.get()->setCellType(new_head_indexes.first,
                                      new_head_indexes.second,
                                      CELL_TYPE::SNAKE);

    prev_direction = next_direction;

    return true;
}

bool Snake::CanITurnThisDirection(DIRECTION next_direction) 
{
    switch (next_direction) {
        case UP:
        {
            return prev_direction != DOWN;
        }
        case DOWN:
        {
            return prev_direction != UP;
        }
        case LEFT:
        {
            return prev_direction != RIGHT;
        }
        case RIGHT:
        {
            return prev_direction != LEFT;
        }
    }
}