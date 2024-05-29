#include "GameBoard.h"


GameBoard::GameBoard(int screen_width,
                     int screen_height)
    :
    game_board_vector(),
    screen_width_px(screen_width),
    screen_height_px(screen_height),
    cell_width_px(screen_height_px  / number_cells_height)
{
    InitializeGameBoardVector();
}

GameBoard::~GameBoard()
{
}


void GameBoard::InitializeGameBoardVector()
{
    for (int row = 0; row < number_cells_height; row++)
    {
        
        std::vector<CELL_TYPE> temp;
        
        for (int col = 0; col < number_cells_width; col++)
        {
        
            temp.push_back(CELL_TYPE::NONE);
        }

        game_board_vector.push_back(temp);
    }
}

void GameBoard::DrawGameBoard(SDL_Renderer* renderer)
{


    for (int row = 0; row < game_board_vector.size(); row++)
    {
        for (int col = 0; col < game_board_vector.at(row).size(); col++)
        {

            DrawGameBoardAtIndice(renderer, row, col);

        }
    }

    SDL_RenderPresent(renderer);
}

void GameBoard::DrawGameBoardAtIndice(SDL_Renderer* renderer, 
                                      const int& row, 
                                      const int& col)
{                    // R  G  B  A
    SDL_Color color = { 0, 0, 0, 255 };

    switch (getCellTypeAtIndex(row, col))
    {
        case NONE:
        {
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }
        default:
        {
            break;
        }
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect current_block_rec;

    current_block_rec.x = cell_width_px * col + line_between_cells_offset + (screen_width_px / 2 - ((number_cells_width * cell_width_px)/2));
    current_block_rec.y = cell_width_px * row + line_between_cells_offset;
    current_block_rec.w = cell_width_px - line_between_cells_offset;
    current_block_rec.h = cell_width_px - line_between_cells_offset;

    SDL_RenderFillRect(renderer, &current_block_rec);

}