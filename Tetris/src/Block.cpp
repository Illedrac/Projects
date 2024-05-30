#include "Block.h"

Block::Block(BLOCK_TYPE type)
    :
    block_positions(),
    block_type(type)
{
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col));
}

Block::~Block()
{

}