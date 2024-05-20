#pragma once
#include <vector>
#include <memory>
#include "SDL.h"
#include "Button.h"

class ButtonHandler
{

public:

    ButtonHandler(SDL_Renderer* renderer);

    void DrawButtons(SDL_Renderer* renderer, bool is_paused);

    inline const std::vector<std::shared_ptr<Button>> GetButtonVector() { return button_vector; }

    inline size_t GetButtonVectorSize() { return button_vector.size(); }

private:

    void CreateButtons(SDL_Renderer* renderer);

    std::vector<std::shared_ptr<Button>> button_vector;
};