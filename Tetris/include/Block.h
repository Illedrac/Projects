#pragma once
#include <vector>
#include <utility>


enum BLOCK_TYPE
{
    NONE,
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
    
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    inline const std::vector<std::pair<int, int>>& GetBlockPositionVector() { return block_positions; }
    inline const std::vector<std::pair<int, int>>& GetBlockPositionPreviousVector() { return previous_block_positions; }

    inline BLOCK_TYPE GetBlockType() { return block_type; }

    void RotateBlockLeft();
    void RotateBlockRight();

protected:

    static const int parent_start_row = 0;
    static const int parent_start_col = 5;

    std::vector<std::pair<int, int>> block_positions;
    std::vector<std::pair<int, int>> previous_block_positions;
    BLOCK_TYPE block_type;
    int rotation_state;
};