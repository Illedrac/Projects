#include "ButtonContainer.h"


ButtonContainer::ButtonContainer(std::shared_ptr<SDL_Renderer> renderer) :	
		button_vector(),
		base_project_path(SDL_GetBasePath()),
		default_button_type(BUTTON_TYPE::BUTTON_MAZE)
{
	CreateButtons(renderer);
	DrawButtons(renderer);
}


void ButtonContainer::DrawButtons(std::shared_ptr<SDL_Renderer> renderer) {

	for (Button b : button_vector) {
		SDL_RenderCopy(renderer.get(), b.getTexture(), NULL, &b.getRect());
	}

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


void ButtonContainer::DrawButtonForAMoment(std::shared_ptr<SDL_Renderer> renderer, const BUTTON_TYPE& type){//Button& b) {
	
	Button& current_button = button_vector.at(GetButtonByButtonType(type));

	current_button.setSelected(true);
	SDL_RenderCopy(renderer.get(), current_button.getTexture(), NULL, &current_button.getRect());
	SDL_RenderPresent(renderer.get());
	SDL_Delay(75);
	
	current_button.setSelected(false);
	SDL_RenderCopy(renderer.get(), current_button.getTexture(), NULL, &current_button.getRect());
	SDL_RenderPresent(renderer.get());
}

void ButtonContainer::ButtonPressed(std::shared_ptr<SDL_Renderer> renderer, BUTTON_TYPE& current_button_type, const BUTTON_TYPE& button_type_to_be_selected/*DRAW_TYPE& current_draw_type,*/) {
	
	
	UnselectButton(current_button_type);

	current_button_type = button_type_to_be_selected;
	
	button_vector.at(GetButtonByButtonType(current_button_type)).setSelected(true);
	
	DrawButtons(renderer);
	
	SDL_RenderPresent(renderer.get());

}

// I don't really know how buttons should work in SDL2 so I just create button instances that hold a texture and 
// to check if a user clicks the button I just check x and y values of the mouse click. Not very good but the UI is not the
// focus of this project 
void ButtonContainer::CreateButtons(std::shared_ptr<SDL_Renderer> renderer /*DRAW_TYPE current_draw_type*/) {

	Button Search_button(renderer.get(), "Search_button", base_project_path, 10, BUTTON_TYPE::BUTTON_SEARCH);
	Button Start_button(renderer.get(), "Start_button", base_project_path, 120, BUTTON_TYPE::BUTTON_START);
	Button Finish_button(renderer.get(), "Finish_button", base_project_path, 230, BUTTON_TYPE::BUTTON_FINISH);
	Button Maze_button(renderer.get(), "Maze_button", base_project_path, 340, BUTTON_TYPE::BUTTON_MAZE);
	Button Add_Walls_button(renderer.get(), "Add_Walls_button", base_project_path, 450, BUTTON_TYPE::BUTTON_ADD_WALLS);
	Button Reset_button(renderer.get(), "Reset_button", base_project_path, 560, BUTTON_TYPE::BUTTON_RESET);

	button_vector.push_back(Search_button);
	button_vector.push_back(Start_button);
	button_vector.push_back(Finish_button);
	button_vector.push_back(Maze_button);
	button_vector.push_back(Add_Walls_button);
	button_vector.push_back(Reset_button);

	button_vector.at(GetButtonByButtonType(default_button_type)).setSelected(true);

}

void ButtonContainer::ClearButtons(std::shared_ptr<SDL_Renderer> renderer, BUTTON_TYPE& current_button_type){
	UnselectButton(current_button_type);

	current_button_type = default_button_type;
	//current_draw_type = DRAW_TYPE::DRAW_MAZE;
	
	button_vector.at(GetButtonByButtonType(current_button_type)).setSelected(true);
	DrawButtons(renderer);

	
	for (Button& b : button_vector) {
		UnselectButton(b.getButtonType());
	}
}
