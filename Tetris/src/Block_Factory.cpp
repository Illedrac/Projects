#include "Block_Factory.h"
#include "L_Block.h"
#include "J_Block.h"
#include "O_Block.h"
#include "S_Block.h"
#include "Z_Block.h"
#include "T_Block.h"
#include "I_Block.h"

Block* Block_Factory::getBlock(BLOCK_TYPE type)
{

    switch (type)
    {
        case L:
        {
            return new L_Block();
        }
        case J:
        {
            return new J_Block();
        }
        case O:
        {
            return new O_Block();
        }
        case S:
        {
            return new S_Block();
        }
        case Z:
        {
            return new Z_Block();
        }
        case T:
        {
            return new T_Block();
        }
        case I:
        {
            return new I_Block();
        }
        default:
        {
            return new Block(BLOCK_TYPE::NONE);
            break;
        }
    };

}