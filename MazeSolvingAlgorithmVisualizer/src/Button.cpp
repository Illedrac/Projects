#include <algorithm>
#include "Button.h"
#include "SDL_image.h"

Button::Button(SDL_Renderer* renderer, std::string image_name, std::string base_path, int y, BUTTON_TYPE t) {

	selected = false;

	type = t;

	path_to_image = base_path;
	path_to_image = path_to_image.substr(2, path_to_image.size() - 1);
	std::replace(path_to_image.begin(), path_to_image.end(), '\\', '/');
	path_to_image.append("../Resources/" );
	path_to_image.append(image_name.c_str());
	
	std::string path_to_image_selected = path_to_image;

	path_to_image.append(".PNG");

	path_to_image_selected.append("_selected.PNG");

	SDL_Surface* unselected_image = IMG_Load(path_to_image.c_str());
	SDL_Surface* selected_image = IMG_Load(path_to_image_selected.c_str());

	unselected_texture = SDL_CreateTextureFromSurface(renderer, unselected_image);
	selected_texture = SDL_CreateTextureFromSurface(renderer, selected_image);

	rect.x = 1755;
	rect.y = y;
	rect.w = 150;
	rect.h = 150;
}