#pragma once
#include <vector>
#include <memory>
#include "Button.h"

class ButtonContainer {

public:
	ButtonContainer(std::shared_ptr<SDL_Renderer> renderer);
	
	void DrawButtons(std::shared_ptr<SDL_Renderer> renderer);

	int GetButtonByButtonType(const BUTTON_TYPE& button_type);

	void UnselectButton(const BUTTON_TYPE& type);

	void DrawButtonForAMoment(std::shared_ptr<SDL_Renderer> renderer, const BUTTON_TYPE& type);

	void ButtonPressed(std::shared_ptr<SDL_Renderer> renderer, BUTTON_TYPE& current_button_type, const BUTTON_TYPE& button_type_to_be_selected);

	void CreateButtons(std::shared_ptr<SDL_Renderer> renderer);

	void ClearButtons(std::shared_ptr<SDL_Renderer> renderer, BUTTON_TYPE& current_button_type);

	inline BUTTON_TYPE GetDefaultButtonType() { return default_button_type; }

	inline std::vector<Button> GetButtonVector() { return button_vector; }

private:
	std::vector<Button> button_vector;
	std::string base_project_path;
	BUTTON_TYPE default_button_type;
};