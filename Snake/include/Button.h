#pragma once
#include <string>
#include "SDL.h"

enum BUTTON_TYPE {
	BUTTON_NONE,
	BUTTON_LOGO, // This is bad design
	BUTTON_PLAY,
	BUTTON_RESUME,
	BUTTON_QUIT
};

class Button {

public:
	Button(SDL_Renderer* renderer, 
		   std::string image_name, 
		   const std::string base_path, 
		   const int y, 
		   const BUTTON_TYPE t);

	inline SDL_Texture* getTexture() { return selected ? selected_texture : unselected_texture; }
	inline SDL_Rect& getRect() { return rect; }
	inline BUTTON_TYPE& getButtonType() { return type; }
	inline bool isButtonSelected() { return selected; }

	inline void setSelected(bool b) { selected = b; }

private:
	bool selected;

	BUTTON_TYPE type;

	std::string path_to_image;

	SDL_Texture* unselected_texture;
	SDL_Texture* selected_texture;
	SDL_Rect rect;
};