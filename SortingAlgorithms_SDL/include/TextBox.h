#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include <string>

class TextBox {
public:
	TextBox(SDL_Renderer* renderer, const std::string& font_path, int font_size, int w, int h, const std::string message_text);

	void display(SDL_Renderer* renderer, int x, int y) const;

	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string message_text);

	SDL_Texture* text_texture = nullptr;
	std::string message;
	mutable SDL_Rect text_rect;


};