#include "O_Block.h"

O_Block::O_Block()
    :    Block(BLOCK_TYPE::O)
{
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col + 1));
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col + 1));
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col));
}