#pragma once
#include <vector>
#include <cmath>
#include "Triangle.h"

class ShapeGame {

public:
	ShapeGame();

	void GameLoop();
	void MoveTriangle();
	void RotateTriangle();
	void SutherlandHodgmanAreaCalculation();


	inline float PI() { return 4 * std::atan(1); }


private:

	const float initial_move_velocity = 10.0f;
	const float initial_rotate_velocity = 0.03f;
	const float initial_rotation_x_value = - ( PI() / 2.0f );

	SDL_Renderer* renderer;
	SDL_Window* window;

	const int screen_width_px = 1920;
	const int screen_height_px = 1080;

	std::vector<Triangle> center_triangles;
	Triangle moving_triangle;

	std::vector< SDL_Vertex > moving_triangle_verts_before_rotation;

	float move_velocity;

	float rotation_x;
	float mid_x;
	float mid_y;

	float moving_center_x;
	float moving_center_y;

};