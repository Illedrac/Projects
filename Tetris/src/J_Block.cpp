#include "J_Block.h"

J_Block::J_Block()
    :
    Block(BLOCK_TYPE::J)
{
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 2, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 2, parent_start_col - 1));
}