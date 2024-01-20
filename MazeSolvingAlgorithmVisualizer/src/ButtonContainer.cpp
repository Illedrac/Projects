#include "ButtonContainer.h"


ButtonContainer::ButtonContainer() :
	button_vector(),
	base_project_path(SDL_GetBasePath()),
	default_draw_button_type(BUTTON_TYPE::BUTTON_MAZE),
	default_algorithm_button_type(BUTTON_TYPE::BUTTON_BFS)
{}

ButtonContainer::ButtonContainer(SDL_Renderer* renderer) :	
		button_vector(),
		base_project_path(SDL_GetBasePath()),
		default_draw_button_type(BUTTON_TYPE::BUTTON_MAZE),
		default_algorithm_button_type(BUTTON_TYPE::BUTTON_BFS)
{
	CreateButtons(renderer);
	DrawButtons(renderer);
}


void ButtonContainer::DrawButtons(SDL_Renderer* renderer) {

	// This is bad, I know, 
	SDL_Rect rect;
	rect.x = 1920 - 170;
	rect.y = 0;
	rect.h = 1080 - 89;
	rect.w = 160;

	SDL_SetRenderDrawColor(renderer, 167, 167, 167, 255);
	SDL_RenderFillRect(renderer, &rect);

	rect.x = 1920 - 165;
	rect.y = 65;
	rect.h = 1080 - 230;
	rect.w = 150;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	for (Button& b : button_vector) {
		SDL_RenderCopy(renderer, b.getTexture(), NULL, &b.getRect());
	}

	SDL_RenderPresent(renderer);
}

int ButtonContainer::GetButtonByButtonType(const BUTTON_TYPE& button_type) {
	
	for (int i = 0; i < button_vector.size(); ++i) {
		if (button_vector.at(i).getButtonType() == button_type)
			return i;
	}

	return -1;
}


void ButtonContainer::UnselectButton(const BUTTON_TYPE& type) {
	
	button_vector.at(GetButtonByButtonType(type)).setSelected(false);
}


void ButtonContainer::DrawButtonForAMoment(SDL_Renderer* renderer, const BUTTON_TYPE& type){//Button& b) {
	
	Button& current_button = button_vector.at(GetButtonByButtonType(type));

	current_button.setSelected(true);
	SDL_RenderCopy(renderer, current_button.getTexture(), NULL, &current_button.getRect());
	SDL_RenderPresent(renderer);
	SDL_Delay(75);
	
	current_button.setSelected(false);
	SDL_RenderCopy(renderer, current_button.getTexture(), NULL, &current_button.getRect());
	SDL_RenderPresent(renderer);
}

void ButtonContainer::ButtonPressed(SDL_Renderer* renderer, BUTTON_TYPE& current_button_type, const BUTTON_TYPE& button_type_to_be_selected) {
	
	if (button_type_to_be_selected != BUTTON_TYPE::BUTTON_DFS || button_type_to_be_selected != BUTTON_TYPE::BUTTON_BFS) {
		UnselectButton(current_button_type);
		current_button_type = button_type_to_be_selected;
	}

	button_vector.at(GetButtonByButtonType(current_button_type)).setSelected(true);

	DrawButtons(renderer);
	

}

// I don't really know how buttons should work in SDL2 so I just create button instances that hold a texture and 
// to check if a user clicks the button I just check x and y values of the mouse click. Not very good but the UI is not the
// focus of this project 
void ButtonContainer::CreateButtons(SDL_Renderer* renderer /*DRAW_TYPE current_draw_type*/) {

	int num_buttons = 8;

	const std::vector<std::string> button_strings_in_order = { "Start", "Finish", "Maze", "Add_Walls", "BFS", "DFS", "Search", "Reset" };
	const std::vector<BUTTON_TYPE> button_types_in_order = { BUTTON_START, BUTTON_FINISH, BUTTON_MAZE, BUTTON_ADD_WALLS, BUTTON_BFS, BUTTON_DFS, BUTTON_SEARCH, BUTTON_RESET };
	
	for (int i = 0; i < num_buttons; i++) {
		Button current_button(renderer, button_strings_in_order.at(i) + "_button", base_project_path, (30 + 110 * i), button_types_in_order.at(i));
		button_vector.push_back(current_button);
	}
	
	button_vector.at(GetButtonByButtonType(default_draw_button_type)).setSelected(true);
	button_vector.at(GetButtonByButtonType(BUTTON_TYPE::BUTTON_BFS)).setSelected(true);
}

void ButtonContainer::ClearButtons(SDL_Renderer* renderer, BUTTON_TYPE& current_button_type){
	
	UnselectButton(current_button_type);

	current_button_type = default_draw_button_type;

	
	button_vector.at(GetButtonByButtonType(current_button_type)).setSelected(true);
	button_vector.at(GetButtonByButtonType(default_algorithm_button_type)).setSelected(true);

	
	DrawButtons(renderer);

	
	for (Button& b : button_vector) {
		UnselectButton(b.getButtonType());
	}
}
