#include "SDL.h"
#include <utility>
#include <span>
#include "ShapeGame.h"


int WinMain() {

	SDL_Init(SDL_INIT_EVERYTHING);

	ShapeGame SG;
	SG.GameLoop();
}

ShapeGame::ShapeGame() :
	renderer(),
	window(),
	center_triangles(),
	moving_triangle(),
	moving_triangle_verts_before_rotation(),
	move_velocity(initial_move_velocity),
	rotation_x(initial_rotation_x_value),
	mid_x(screen_width_px / 2),
	mid_y(screen_height_px / 2),
	moving_center_x(),
	moving_center_y()
{

	SDL_CreateWindowAndRenderer(screen_width_px, screen_height_px, NULL, &window, &renderer);

	int side_length = 250;

	Triangle outer_triangle(mid_x, mid_y, side_length, TRIANGLE_TYPE::CENTER_OUTER);

	side_length -= 10;

	Triangle inner_triangle(mid_x, mid_y, side_length, TRIANGLE_TYPE::CENTER_INNER);

	center_triangles.push_back(outer_triangle);
	center_triangles.push_back(inner_triangle);

	moving_triangle = Triangle(mid_x, 150, side_length, TRIANGLE_TYPE::MOVING);

}


void ShapeGame::GameLoop() {
	
	const int FPS = 120;
	const int frame_delay = 1000 / FPS;

	// More variables to control frame rate
	Uint32 frame_start;
	int frame_time;

	bool continue_running_program = true;
	bool should_move_triangle = true;
	bool should_rotate_triangle = false;
	bool store_initial_vertexes = true;

	SDL_Event event;

	while (continue_running_program) {

		frame_start = SDL_GetTicks();
		
		SDL_PollEvent(&event);

		switch (event.type) {

			case SDL_EventType::SDL_QUIT: {
				continue_running_program = false;
				break;
			}

			case SDL_EventType::SDL_KEYDOWN: {

				switch (event.key.keysym.scancode) {

				case SDL_SCANCODE_ESCAPE:
					continue_running_program = false;
					break;

				case SDL_SCANCODE_SPACE:
					if (should_move_triangle) {
						should_move_triangle = false;
						should_rotate_triangle = true;
						move_velocity = initial_rotate_velocity;
					}
					else if (should_rotate_triangle) {
						should_rotate_triangle = false;
					}

					break;
				
				case SDL_SCANCODE_R: {
					
					move_velocity = initial_move_velocity;
					rotation_x = initial_rotation_x_value;

					float x = moving_triangle.GetInitialXPos();
					float y = moving_triangle.GetInitialYPos();
					float side_length = moving_triangle.GetInitialSideLength();

					std::vector<SDL_Vertex> verts =
					{
						{ SDL_FPoint{ x, (float)(y - ((std::sqrt(3) / 3) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
						{ SDL_FPoint{ x + side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
						{ SDL_FPoint{ x - side_length / 2, (float)(y + ((std::sqrt(3) / 6) * side_length))}, SDL_Color{ 255, 255, 255, 255 }, SDL_FPoint{ 0 }, },
					};

					moving_triangle.SetVerts(verts);
					should_move_triangle = true;
					store_initial_vertexes = true;
				}
					
				
				default:
					break;
				}
			}

			default:
				break;

		}
	
		if (should_move_triangle) {
			MoveTriangle();
		}
		else if (should_rotate_triangle){

			if (store_initial_vertexes) {
				// Make a copy of the inital vertexes before rotation so we know where to rotate around
				// There's probably a better way of doing this
				moving_triangle_verts_before_rotation = *moving_triangle.GetVerts();
				
				moving_center_x = moving_triangle_verts_before_rotation.at(0).position.x;
				moving_center_y = moving_triangle_verts_before_rotation.at(0).position.y + ( moving_triangle.GetInitialSideLength() / std::sqrt(3) );

				store_initial_vertexes = false;


			}
			RotateTriangle();
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		for (int i = 0; i < 2; i++) {
			Triangle& cur = center_triangles.at(i);
			SDL_RenderGeometry(renderer, nullptr, cur.GetVerts()->data(), cur.GetVerts()->size(), nullptr, 0);
		}

		SDL_RenderGeometry(renderer, nullptr, moving_triangle.GetVerts()->data(), moving_triangle.GetVerts()->size(), nullptr, 0);

		SDL_RenderPresent(renderer);


		frame_time = SDL_GetTicks() - frame_start;

		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}

	}
}

void ShapeGame::MoveTriangle() {


	if (moving_triangle.GetVerts()->at(1).position.y > 1070.0f || moving_triangle.GetVerts()->at(0).position.y < 10.0f) {
		move_velocity *= -1;
	}

	moving_triangle.GetVerts()->at(0).position.y += move_velocity;
	moving_triangle.GetVerts()->at(1).position.y += move_velocity;
	moving_triangle.GetVerts()->at(2).position.y += move_velocity;


}

void ShapeGame::RotateTriangle() {
					
																// size                                                               center offset
	moving_triangle.GetVerts()->at(0).position.y = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::sin( rotation_x ) + moving_center_y;
	moving_triangle.GetVerts()->at(0).position.x = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::cos( rotation_x ) + moving_center_x;

	moving_triangle.GetVerts()->at(1).position.y = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::sin(rotation_x - (2 * PI() / 3)) + moving_center_y;
	moving_triangle.GetVerts()->at(1).position.x = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::cos(rotation_x - (2 * PI() / 3)) + moving_center_x;

	moving_triangle.GetVerts()->at(2).position.y = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::sin(rotation_x + (2 * PI() / 3)) + moving_center_y;
	moving_triangle.GetVerts()->at(2).position.x = (moving_triangle.GetInitialSideLength() / std::sqrt(3)) * std::cos(rotation_x + (2 * PI() / 3)) + moving_center_x;


	rotation_x += move_velocity;

}

void ShapeGame::SutherlandHodgmanAreaCalculation() {

	std::vector<SDL_Vertex> result;




	/*
	std::span<vec2 const> subject_polygon, std::span<vec2 const> clip_polygon) {
		if (clip_polygon.empty() || subject_polygon.empty()) {
			return {};
		}

		std::vector<vec2> ring{ subject_polygon.begin(), subject_polygon.end() };

		vec2 p1 = clip_polygon[clip_polygon.size() - 1];

		std::vector<vec2> input;

		for (vec2 p2 : clip_polygon) {
			input.clear();
			input.insert(input.end(), ring.begin(), ring.end());
			vec2 s = input[input.size() - 1];

			ring.clear();

			for (vec2 e : input) {
				if (is_inside(e, p1, p2)) {
					if (!is_inside(s, p1, p2)) {
						ring.push_back(intersection(p1, p2, s, e));
					}

					ring.push_back(e);
				}
				else if (is_inside(s, p1, p2)) {
					ring.push_back(intersection(p1, p2, s, e));
				}

				s = e;
			}

			p1 = p2;
		}

		return ring;

		*/
}
