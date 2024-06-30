#include "GameBoard.h"


GameBoard::GameBoard(int screen_width,
                     int screen_height)
    :
    game_board_vector(),
    screen_width_px(screen_width),
    screen_height_px(screen_height),
    cell_width_px(screen_height_px  / number_cells_height)
{
    InitializeGameBoardVector();
}

GameBoard::~GameBoard()
{
}


void GameBoard::InitializeGameBoardVector()
{
    for (int row = 0; row < number_cells_height; row++)
    {
        
        std::vector<BLOCK_TYPE> temp;
        
        for (int col = 0; col < number_cells_width; col++)
        {
        
            temp.push_back(BLOCK_TYPE::NONE);
        }

        game_board_vector.push_back(temp);
    }
}

void GameBoard::DrawGameBoard(SDL_Renderer* renderer)
{


    for (int row = 0; row < game_board_vector.size(); row++)
    {
        for (int col = 0; col < game_board_vector.at(row).size(); col++)
        {

            DrawGameBoardAtIndice(renderer, row, col);

        }
    }

    SDL_RenderPresent(renderer);
}

void GameBoard::DrawGameBoardAtIndice(SDL_Renderer* renderer, 
                                      const int& row, 
                                      const int& col)
{                    // R  G  B  A
    SDL_Color color = { 0, 0, 0, 255 };

    switch (getCellTypeAtIndex(row, col))
    {
        case NONE:
        {
            color.r = 255;
            color.g = 255;
            color.b = 255;
            break;
        }
        case O:
        {
            color.r = 255;
            color.g = 255;
            color.b = 0;
            break;
        }
        case I:
        {
            color.r = 57;
            color.g = 199;
            color.b = 204;
            break;
        }
        case J:
        {
            color.r = 215;
            color.g = 91;
            color.b = 222;
            break;
        }
        case L:
        {
            color.r = 214;
            color.g = 133;
            color.b = 26;
            break;
        }
        case S:
        {
            color.r = 186;
            color.g = 30;
            color.b = 13;
            break;
        }
        case Z:
        {
            color.r = 77;
            color.g = 219;
            color.b = 82;
            break;
        }
        case T:
        {
            color.r = 142;
            color.g = 0;
            color.b = 161;
            break;
        }
        default:
        {
            break;
        }
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect current_block_rec;

    current_block_rec.x = cell_width_px * col + line_between_cells_offset + (screen_width_px / 2 - ((number_cells_width * cell_width_px)/2));
    current_block_rec.y = cell_width_px * row + line_between_cells_offset;
    current_block_rec.w = cell_width_px - line_between_cells_offset;
    current_block_rec.h = cell_width_px - line_between_cells_offset;

    SDL_RenderFillRect(renderer, &current_block_rec);

}

void GameBoard::UpdateCurrentBlockPosition(const BLOCK_TYPE& type, 
                                           const std::vector<std::pair<int, int>>& position_vector,
                                           const std::vector<std::pair<int, int>>& previous_position_vector)
{

    for (const std::pair<int, int>& current_subblock_pair : previous_position_vector)
    {
        if (current_subblock_pair.first < number_cells_height)
            setCellTypeAtIndex(current_subblock_pair.first, current_subblock_pair.second, BLOCK_TYPE::NONE);

    }

    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {
        if(current_subblock_pair.first < number_cells_height)
            setCellTypeAtIndex(current_subblock_pair.first, current_subblock_pair.second, type);
    
    }

}

void GameBoard::CheckIfClearRow()
{

    for (int row = number_cells_height - 1; row >= 0; row--)
    {
        bool clearRow = true;
        bool foundBlock = false;

        for (int col = number_cells_width - 1; col >= 0; col--)
        {
            BLOCK_TYPE current_type = getCellTypeAtIndex(row, col);
            if (clearRow && current_type == BLOCK_TYPE::NONE)
                clearRow = false;
            else if (!foundBlock && current_type != BLOCK_TYPE::NONE)
                foundBlock = true;
        }
        if (!foundBlock)
            return;

        if(clearRow)
            ClearCurrentRow(row);
    }
}

void GameBoard::ClearCurrentRow(const int& in_row)
{
    for (int row = in_row; row >= 1; row--)
    {

        for (int col = number_cells_width - 1; col >= 0; col--)
        {
            setCellTypeAtIndex(row, col, getCellTypeAtIndex(row - 1, col));
        }
    }
}

bool GameBoard::CanBlockMoveDown(const std::vector<std::pair<int, int>>& position_vector)
{

    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {
        std::pair<int, int> block_below = std::make_pair<int, int>(current_subblock_pair.first + 1, current_subblock_pair.second + 0);
        
        if(std::find(position_vector.begin(), position_vector.end(), block_below) == std::end(position_vector))
        {
                                  
            if (!IsBlockInBounds(block_below))
                return false;
        
            if (getCellTypeAtIndex(block_below.first, block_below.second) != NONE)
                return false;
        }
    }

    return true;

}

bool GameBoard::CanBlockMoveLeft(const std::vector<std::pair<int, int>>& position_vector)
{

    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {
        std::pair<int, int> block_to_the_left = std::make_pair<int, int>(current_subblock_pair.first + 0, current_subblock_pair.second - 1);

        if (std::find(position_vector.begin(), position_vector.end(), block_to_the_left) == std::end(position_vector))
        {

            if (!IsBlockInBounds(block_to_the_left))
                return false;

            if (getCellTypeAtIndex(block_to_the_left.first, block_to_the_left.second) != NONE)
                return false;
        }
    }

    return true;

}

bool GameBoard::CanBlockMoveRight(const std::vector<std::pair<int, int>>& position_vector)
{

    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {
        std::pair<int, int> block_to_the_right = std::make_pair<int, int>(current_subblock_pair.first + 0, current_subblock_pair.second + 1);

        if (std::find(position_vector.begin(), position_vector.end(), block_to_the_right) == std::end(position_vector))
        {

            if (!IsBlockInBounds(block_to_the_right))
                return false;

            if (getCellTypeAtIndex(block_to_the_right.first, block_to_the_right.second) != NONE)
                return false;
        }
    }

    return true;

}

bool GameBoard::CanBlockRotateRight(const std::vector<std::pair<int, int>>& position_vector)
{


    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {

        int x = current_subblock_pair.first;
        int y = current_subblock_pair.second;

        int temp_new_x = position_vector.at(1).first + (y - position_vector.at(1).second);
        int temp_new_y = position_vector.at(1).second - (x - position_vector.at(1).first);
        
        std::pair<int, int> temp_rotated_block(temp_new_x, temp_new_y);

        if (std::find(position_vector.begin(), position_vector.end(), temp_rotated_block) == std::end(position_vector))
        {

            if (!IsBlockInBounds(temp_rotated_block))
                return false;

            if (getCellTypeAtIndex(temp_rotated_block.first, temp_rotated_block.second) != NONE)
                return false;
        }
    }

    return true;

}

bool GameBoard::CanBlockRotateLeft(const std::vector<std::pair<int, int>>& position_vector)
{


    for (const std::pair<int, int>& current_subblock_pair : position_vector)
    {

        int x = current_subblock_pair.first;
        int y = current_subblock_pair.second;

        int temp_new_x = position_vector.at(1).first - (y - position_vector.at(1).second);
        int temp_new_y = position_vector.at(1).second + (x - position_vector.at(1).first);

        std::pair<int, int> temp_rotated_block(temp_new_x, temp_new_y);

        if (std::find(position_vector.begin(), position_vector.end(), temp_rotated_block) == std::end(position_vector))
        {

            if (!IsBlockInBounds(temp_rotated_block))
                return false;

            if (getCellTypeAtIndex(temp_rotated_block.first, temp_rotated_block.second) != NONE)
                return false;
        }
    }

    return true;

}

bool GameBoard::IsBlockInBounds(const std::pair<int, int>& block)
{
    return (block.first >= 0 && 
            block.first < number_cells_height && 
            block.second >= 0 && 
            block.second < number_cells_width) ? true : false;
}
