#pragma once
#include <vector>
#include <memory>
#include "Button.h"

class ButtonContainer {

public:
	ButtonContainer();
	ButtonContainer(SDL_Renderer* renderer);
	
	void DrawButtons(SDL_Renderer* renderer);

	int GetButtonByButtonType(const BUTTON_TYPE& button_type);

	void UnselectButton(const BUTTON_TYPE& type);

	void DrawButtonForAMoment(SDL_Renderer* renderer, const BUTTON_TYPE& type);

	void ButtonPressed(SDL_Renderer* renderer, BUTTON_TYPE& current_button_type, const BUTTON_TYPE& button_type_to_be_selected);

	void CreateButtons(SDL_Renderer* renderer);

	void ClearButtons(SDL_Renderer* renderer, BUTTON_TYPE& current_button_type);

	inline BUTTON_TYPE GetDefaultButtonType() { return default_draw_button_type; }

	inline std::vector<Button> GetButtonVector() { return button_vector; }

private:
	std::vector<Button> button_vector;
	std::string base_project_path;
	BUTTON_TYPE default_draw_button_type;
	BUTTON_TYPE default_algorithm_button_type;
};