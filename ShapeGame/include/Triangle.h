#pragma once
#include "SDL.h"
#include <vector>

enum TRIANGLE_TYPE {
	CENTER_OUTER,
	CENTER_INNER,
	MOVING
};


class Triangle {

public:
	Triangle();
	Triangle(const float x, const float y, const int side_length, TRIANGLE_TYPE tri_type);

	inline std::vector< SDL_Vertex >* GetVerts() { return &verts; }
	inline float GetInitialXPos() { return initial_x_pos; }
	inline float GetInitialYPos() { return initial_y_pos; }
	inline float GetInitialSideLength() { return initial_side_length; }

	inline void SetVerts(std::vector<SDL_Vertex>& v) { verts = v; }
	
private:

	std::vector< SDL_Vertex > verts;
	float initial_x_pos;
	float initial_y_pos;
	float initial_side_length;
	TRIANGLE_TYPE initial_tri_type;
}; 