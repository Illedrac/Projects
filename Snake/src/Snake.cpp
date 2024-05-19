#include "Snake.h"
#include "GameBoard.h"
#include "FoodHandler.h"

Snake::Snake() :
    snake_body_indexes(),
    move_queue(),
    prev_direction(NONE),
    hit_wall_once(false)
{
    snake_body_indexes.push_back(std::make_pair(default_snake_x, default_snake_y));
}


void Snake::InitSnake(std::shared_ptr<GameBoard> game_board_ptr) 
{
    game_board_ptr.get()->setCellType(snake_body_indexes.at(0).first, snake_body_indexes.at(0).second, CELL_TYPE::SNAKE);
}

void Snake::Reset(std::shared_ptr<GameBoard> game_board_ptr)
{
    prev_direction = NONE;
    snake_body_indexes.clear();
    snake_body_indexes.push_back(std::make_pair(default_snake_x, default_snake_y));
    game_board_ptr.get()->setCellType(default_snake_x, default_snake_y, SNAKE);
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

    //Update the new head's position based on whatever the next direction is
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
    //I swear that the original snake gave a two frame grace for out of bounds 
    //Such that, if you hit a wall, you have one more frame-worth of time to not hit the wall
    //However, looking it up, I can't seem to find anyone who says this
    //So I've implemented this two frame grace anyway
    if (new_head_indexes.first < 0 ||
        new_head_indexes.first > game_board_ptr.get()->getMaxHeight() ||
        new_head_indexes.second < 0 ||
        new_head_indexes.second > game_board_ptr.get()->getMaxWidth())
    {
        //If we've already hit the wall once and we're still out of bounds, end game
        if (hit_wall_once) 
        {
            return false;
        }
        //Otherwise, this is the first time we've hit the wall so set the boolean to true and continue running the program
        //One note here, we don't update the position of the snake since it would've been moved to off the screen
        else
        {
            hit_wall_once = true;
            return true;
        }
    }
    //If we hit the wall in the previous frame but now we're not, reset the boolean to false
    else if (hit_wall_once)
    {
        hit_wall_once = false;
    }

    //Tail collision checking 
    if (game_board_ptr.get()->getCellType(new_head_indexes.first, new_head_indexes.second) == SNAKE) return false;

    //If we're not on food, update the tail's position to be empty and remove it from the vector
    if (!game_board_ptr.get()->IsOnFood(new_head_indexes.first, new_head_indexes.second))
    {
        game_board_ptr.get()->setCellType(snake_body_indexes.at(snake_body_indexes.size() - 1).first,
                                          snake_body_indexes.at(snake_body_indexes.size() - 1).second,
                                          CELL_TYPE::EMPTY);

        snake_body_indexes.pop_back();
    }
    //Otherwise, we're on food. Therefore, don't remove the tail 
    //Such that the snake grows by one
    else 
    {
        
        game_board_ptr.get()->setFoodExist(false);
        game_board_ptr.get()->setFood(-1, -1);
    }

    //Insert the new head into the vector
    //This implmentation is likely pretty inefficient and I understand that
    //However, it was easy / fun to implement so that's what matters
    snake_body_indexes.insert(snake_body_indexes.begin(), new_head_indexes);

    game_board_ptr.get()->setCellType(new_head_indexes.first,
                                      new_head_indexes.second,
                                      CELL_TYPE::SNAKE);

    //Update previous direction
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
        default:
        {
            return false;
        }
    }
}