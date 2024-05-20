#pragma once
#include "SDL_ttf.h"
#include <string>

class ScoreBoard
{
public:

    ScoreBoard(std::string path_to_font);

	void DisplayScore(SDL_Renderer* renderer,
					  const int score);
	
	void DisplayGameOver(SDL_Renderer* renderer,
						 int last_score,
						 int screen_width_px,
						 int screen_height_px);

private:

	void LoadFont(const std::string& font_path, 
				  const int font_size);

	SDL_Texture* text_texture = nullptr;
	
	SDL_Rect text_rect;

	TTF_Font* font;

};