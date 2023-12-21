#pragma once
#include <string>
#include "SDL.h"

enum BUTTON_TYPE {
	BUTTON_SEARCH,
	BUTTON_START,
	BUTTON_FINISH,
	BUTTON_MAZE,
	BUTTON_RESET,
	BUTTON_ADD_WALLS
};

class Button {

public:
	Button(SDL_Renderer* renderer, std::string image_name, std::string base_path, int y, BUTTON_TYPE t);

	inline SDL_Texture* getTexture() { return texture; }
	inline SDL_Rect& getRect() { return rect; }
	inline BUTTON_TYPE& getButtonType() { return type; }

private:
	BUTTON_TYPE type;
	std::string path_to_image;
	SDL_Texture* texture;
	SDL_Rect rect;
};