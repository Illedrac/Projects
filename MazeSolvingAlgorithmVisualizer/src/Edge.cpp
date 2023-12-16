#include "Edge.h"

Edge::Edge(int row, int col) :
	row(row),
	col(col),
	prev_edge(nullptr)
{
}

Edge::Edge(int row, int col, Edge* p_edge) :
	row(row),
	col(col),
	prev_edge(p_edge)
{
}

void Edge::setPrevEdge(Edge* p_edge) {
	prev_edge = p_edge;
}

bool Edge::operator==(const Edge& rhs)
{
	return getRow() == rhs.row && getCol() == rhs.col;
}