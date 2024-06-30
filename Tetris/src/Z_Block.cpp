#include "Z_Block.h"

Z_Block::Z_Block()
    : Block(BLOCK_TYPE::Z)
{
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col - 1));
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col));
    block_positions.push_back(std::make_pair(parent_start_row + 1, parent_start_col + 1));
}