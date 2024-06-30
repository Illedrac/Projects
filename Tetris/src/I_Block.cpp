#include "I_Block.h"

I_Block::I_Block()
    :
    Block(BLOCK_TYPE::I)
{
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 2, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 3, parent_start_col));
}