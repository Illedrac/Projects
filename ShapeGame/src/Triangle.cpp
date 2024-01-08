#include "Triangle.h"
#include <cmath>

Triangle::Triangle() :
	verts(),
	initial_x_pos(),
	initial_y_pos(),
	initial_side_length(),
	initial_tri_type() {

}

Triangle::Triangle(const float x, const float y, const int side_length, TRIANGLE_TYPE tri_type) :
	verts(),
	initial_x_pos(x),
	initial_y_pos(y),
	initial_side_length(side_length),
	initial_tri_type(tri_type)
{

	if (tri_type == TRIANGLE_TYPE::CENTER_OUTER) {
			
		verts =
		{
			{ SDL_FPoint{ x, (float)(y - ((std::sqrt(3) / 3) * side_length))}, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x + side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x - side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
		};

	}
	else if (tri_type == TRIANGLE_TYPE::CENTER_INNER){
			
		verts =
		{
			{ SDL_FPoint{ x, (float)(y - ((std::sqrt(3) / 3) * side_length))}, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x + side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x - side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 0, 0, 0, 255 }, SDL_FPoint{ 0 }, },
		};

	}

	else if (tri_type == TRIANGLE_TYPE::MOVING){

		verts =
		{
			{ SDL_FPoint{ x, (float)(y - ((std::sqrt(3) / 3) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x + side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
			{ SDL_FPoint{ x - side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
		};

	}
}