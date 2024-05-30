#pragma once
#include <vector>
#include <utility>


enum BLOCK_TYPE
{
    NONE,
    WALL,
    L,
    J,
    O,
    S,
    Z,
    T,
    I
};


class Block
{

public:
    Block(BLOCK_TYPE type);
    ~Block();

    inline const std::vector<std::pair<int, int>>& GetBlockPositionVector() { return block_positions; }

    inline BLOCK_TYPE GetBlockType() { return block_type; }

protected:

    static const int parent_start_row = 1;
    static const int parent_start_col = 5;

    std::vector<std::pair<int, int>> block_positions;
    BLOCK_TYPE block_type;
};