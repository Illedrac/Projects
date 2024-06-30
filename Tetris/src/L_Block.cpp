#include "L_Block.h"

L_Block::L_Block()
    : Block(BLOCK_TYPE::L)
{
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 2, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 2, parent_start_col + 1));
}

