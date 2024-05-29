#include <vector>
#include "SDL.h"

enum CELL_TYPE
{
    NONE,
    WALL,
    BLOCK
};

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
    
    inline CELL_TYPE getCellTypeAtIndex(const int& row, const int& col) { return game_board_vector.at(row).at(col); }
private:

    void InitializeGameBoardVector();

    std::vector<std::vector<CELL_TYPE>> game_board_vector;

    int screen_width_px;
    int screen_height_px;
    int cell_width_px;
};