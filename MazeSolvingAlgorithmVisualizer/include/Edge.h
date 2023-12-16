#pragma once

class Edge {

public:
	Edge(int row, int col);
	Edge(int row, int col, Edge* prev_edge);

	inline int getRow() { return row; }
	inline int getCol() { return col; }
	inline Edge* getPrevEdge() { return prev_edge; }
	
	void setPrevEdge(Edge* p_edge);
	bool operator==(const Edge& rhs);

private:
	int row;
	int col;
	
	Edge* prev_edge;
};