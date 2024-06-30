#include "T_Block.h"

T_Block::T_Block()
    :
    Block(BLOCK_TYPE::T)
{
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col - 1));
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col + 1));
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col ));
}