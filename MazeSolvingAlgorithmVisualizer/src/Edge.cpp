#include "Edge.h"

Edge::Edge(int row, int col) :
	row(row),
	col(col)
{
}

bool Edge::operator==(const Edge& rhs)
{
	return getRow() == rhs.row && getCol() == rhs.col;
}