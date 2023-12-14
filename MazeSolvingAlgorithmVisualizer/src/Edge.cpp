#include "Edge.h"

Edge::Edge(int row, int col, int prev_row, int prev_col) :
	row(row),
	col(col),
	prev_row(prev_row),
	prev_col(prev_col)
{
}


bool Edge::operator==(const Edge& rhs)
{
	return getRow() == rhs.row && getCol() == rhs.col;
}