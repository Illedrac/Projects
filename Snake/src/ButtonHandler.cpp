#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(SDL_Renderer* renderer)
    :
    button_vector()
{
    
    CreateButtons(renderer);

}

// I am really bad at UI and such so this is a nightmare, I know
void ButtonHandler::CreateButtons(SDL_Renderer* renderer) 
{

	const std::string button_strings_in_order[4] = {"Snake_Logo","Play","Resume", "Quit" };
	const BUTTON_TYPE button_types_in_order[4] = { BUTTON_LOGO, BUTTON_PLAY, BUTTON_RESUME, BUTTON_QUIT };
	
	button_vector.push_back(
					std::make_shared<Button>(renderer, 
											button_strings_in_order[0], 
											SDL_GetBasePath(), 
											1080 / 4 + 200 * 0, // I know this is bad :(
											button_types_in_order[0] ) );
	

	button_vector.push_back(
					std::make_shared<Button>(renderer,
											button_strings_in_order[1],
											SDL_GetBasePath(),
											1080 / 4 + 200 * 1, // I know this is bad :(
											button_types_in_order[1]));


	button_vector.push_back(
					std::make_shared<Button>(renderer,
											button_strings_in_order[2],
											SDL_GetBasePath(),
											1080 / 4 + 200 * 1, // I know this is bad :(
											button_types_in_order[2]));


	button_vector.push_back(
					std::make_shared<Button>(renderer,
											button_strings_in_order[3],
											SDL_GetBasePath(),
											1080 / 4 + 200 * 2, // I know this is bad :(
											button_types_in_order[3]));

}

void ButtonHandler::DrawButtons(SDL_Renderer* renderer, bool is_paused)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderCopy(renderer, button_vector.at(0).get()->getTexture(), NULL, &button_vector.at(0).get()->getRect());
	
	if (!is_paused) 
	{
		SDL_RenderCopy(renderer, button_vector.at(1).get()->getTexture(), NULL, &button_vector.at(1).get()->getRect());
	}
	else
	{
		SDL_RenderCopy(renderer, button_vector.at(2).get()->getTexture(), NULL, &button_vector.at(2).get()->getRect());
	}

	
	SDL_RenderCopy(renderer, button_vector.at(3).get()->getTexture(), NULL, &button_vector.at(3).get()->getRect());
	

	SDL_RenderPresent(renderer);

}