#pragma once

class Edge {

public:
	Edge(int row, int col);

	const inline int getRow() { return row; }
	const inline int getCol() { return col; }
	
	bool operator==(const Edge& rhs);

private:
	int row;
	int col;
};