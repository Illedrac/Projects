#include <algorithm>
#include "Button.h"
#include "SDL_image.h"

Button::Button(SDL_Renderer* renderer, 
			   std::string image_name, 
			   const std::string base_path, 
			   const int y, 
			   const BUTTON_TYPE t) 
{

	selected = false;

	type = t;
	
	if (t != BUTTON_LOGO)
	{
		image_name += "_button";
	}

	path_to_image = base_path;
	path_to_image = path_to_image.substr(2, path_to_image.size() - 1);
	std::replace(path_to_image.begin(), path_to_image.end(), '\\', '/');
	path_to_image.append("../Resources/");
	path_to_image.append(image_name.c_str());

	std::string path_to_image_selected = path_to_image;

	path_to_image.append(".PNG");

	path_to_image_selected.append("_highlighted.PNG");

	SDL_Surface* unselected_image = IMG_Load(path_to_image.c_str());
	SDL_Surface* selected_image = IMG_Load(path_to_image_selected.c_str());

	unselected_texture = SDL_CreateTextureFromSurface(renderer, unselected_image);

	// This is stupid
	if (t != BUTTON_LOGO)
	{
		selected_texture = SDL_CreateTextureFromSurface(renderer, selected_image);

		rect.x = 1920 / 2 - 150;
		rect.y = y;
		rect.h = 110;
		rect.w = 300;
	}
	else
	{
		selected_texture = SDL_CreateTextureFromSurface(renderer, unselected_image);

		rect.x = 1920 / 2 - 440;
		rect.y = y - 200;
		rect.h = 210;
		rect.w = 880;
	}
}