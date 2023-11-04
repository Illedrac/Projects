#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "TextBox.h"
#include "AlgorithmFactory.h"


class SortingAlgorithmsMain {

public:
	SortingAlgorithmsMain(int width, int height);

	std::string GetFontPath(const std::string& font_name);
	void DisplayTextBoxes(int screen_width);
	void SetAlgorithmType(AlgorithmType algorithm_type, int screen_width);
	void Initialize(int width);
	void DrawInitialArray(int screen_width);
	void ClearScreen();

	SDL_Window* window ;
	SDL_Renderer* renderer ;
	
	Algorithm* sorting_algorithm_implementation;
	std::vector<TextBox*> text_boxes_vector;

};