#include "FoodHandler.h"
#include "GameBoard.h"
#include "random"

bool FoodHandler::SpawnFood(std::shared_ptr<GameBoard> g)
{

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, g.get()->getNumberCells()-1);
   
    int tries = 0;
    //Make sure that a food doesn't already exist on the board
    while(!g.get()->getFoodExist())
    {
        int x = distrib(gen);
        int y = distrib(gen);

        if (g.get()->getCellType(x, y) == CELL_TYPE::EMPTY)
        {
            g.get()->setCellType(x,y, CELL_TYPE::FOOD);
            g.get()->setFoodExist(true);
            g.get()->setFood(x, y);

            return true;
        }
        else
            ++tries;

        if (tries > 150) return false;
    }

    return false;
}