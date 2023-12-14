#pragma once

class Edge {

public:
	Edge(int row, int col, int prev_row, int prev_col);

	inline int getRow() { return row; }
	inline int getCol() { return col; }
	inline int getPrevRow() { return prev_row; }
	inline int getPrevCol() { return prev_col; }

	bool operator==(const Edge& rhs);

private:
	int row;
	int col;
	
	int prev_row;
	int prev_col;
};