#include <vector>
#include "SDL.h"
#include "Block.h"



const int number_cells_width = 12;
const int number_cells_height = 22;
const int line_between_cells_offset = 1;

class GameBoard 
{

public:
    GameBoard(int screen_width,
              int screen_height);

    ~GameBoard();

    void DrawGameBoard(SDL_Renderer* renderer);

    void DrawGameBoardAtIndice(SDL_Renderer* renderer, 
                               const int& row, 
                               const int& col);
    
    inline BLOCK_TYPE getCellTypeAtIndex(const int& row, const int& col) { return game_board_vector.at(row).at(col); }

    inline void setCellTypeAtIndex(const int& row, const int& col, BLOCK_TYPE type) { game_board_vector.at(row).at(col) = type; }

    void UpdateCurrentBlockPosition(const BLOCK_TYPE& type,
                                    const std::vector<std::pair<int, int>>& position_vector,
                                    const std::vector<std::pair<int, int>>& previous_position_vector);

    bool CanBlockMoveDown(const std::vector<std::pair<int, int>>& position_vector);
    bool CanBlockMoveLeft(const std::vector<std::pair<int, int>>& position_vector);
    bool CanBlockMoveRight(const std::vector<std::pair<int, int>>& position_vector);
    bool CanBlockRotateRight(const std::vector<std::pair<int, int>>& position_vector);
    bool CanBlockRotateLeft(const std::vector<std::pair<int, int>>& position_vector);
    bool IsBlockInBounds(const std::pair<int, int>& block);

    void CheckIfClearRow();

private:

    void InitializeGameBoardVector();
    void ClearCurrentRow(const int& in_row);

    std::vector<std::vector<BLOCK_TYPE>> game_board_vector;

    int screen_width_px;
    int screen_height_px;
    int cell_width_px;
};