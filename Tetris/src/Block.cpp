#include "Block.h"

Block::Block(BLOCK_TYPE type)
    :
    block_positions(),
    previous_block_positions(),
    block_type(type),
    rotation_state(0)
{
    block_positions.push_back(std::make_pair(parent_start_row, parent_start_col));
}

Block::~Block()
{

}

void Block::MoveDown()
{
    previous_block_positions = block_positions;

    for (std::pair<int, int>& current_block : block_positions)
    {
        current_block.first += 1;
    }
}

void Block::MoveRight()
{
    previous_block_positions = block_positions;

    for (std::pair<int, int>& current_block : block_positions)
    {
        current_block.second += 1;
    }
}

void Block::MoveLeft()
{
    previous_block_positions = block_positions;

    for (std::pair<int, int>& current_block : block_positions)
    {
        current_block.second -= 1;
    }
}

void Block::RotateBlockLeft()
{
    if (block_type == BLOCK_TYPE::O) return;

    previous_block_positions = block_positions;

    for (std::pair<int, int>& subblock_pair : block_positions)
    {
        int x = subblock_pair.first;
        int y = subblock_pair.second;

        subblock_pair.first = previous_block_positions.at(1).first - (y - previous_block_positions.at(1).second);
        subblock_pair.second = previous_block_positions.at(1).second + (x - previous_block_positions.at(1).first);
    }
}

void Block::RotateBlockRight()
{
    if (block_type == BLOCK_TYPE::O) return;

    previous_block_positions = block_positions;

    for (std::pair<int, int>& subblock_pair : block_positions)
    {
        int x = subblock_pair.first;
        int y = subblock_pair.second;

        subblock_pair.first = previous_block_positions.at(1).first + (y - previous_block_positions.at(1).second);
        subblock_pair.second = previous_block_positions.at(1).second - (x - previous_block_positions.at(1).first);

    }
}
