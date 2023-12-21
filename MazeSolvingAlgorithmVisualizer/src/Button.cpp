#include <algorithm>
#include "Button.h"
#include "SDL_image.h"

Button::Button(SDL_Renderer* renderer, std::string image_name, std::string base_path, int y, BUTTON_TYPE t) {

	type = t;

	path_to_image = base_path;
	path_to_image = path_to_image.substr(2, path_to_image.size() - 1);
	std::replace(path_to_image.begin(), path_to_image.end(), '\\', '/');
	path_to_image.append("../Resources/" );
	path_to_image.append(image_name.c_str());


	SDL_Surface* image = IMG_Load(path_to_image.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, image);

	rect.x = 1760;
	rect.y = y;
	rect.w = 140;
	rect.h = 100;
}