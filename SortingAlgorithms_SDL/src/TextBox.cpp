#include "TextBox.h"

TextBox::TextBox(SDL_Renderer* renderer, const std::string& font_path, int font_size, int w, int h, const std::string message_text)
{
    if (TTF_Init() == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to Initialize TTF", NULL);
        exit(2);
    }
    
    text_rect.w = w;
    text_rect.h = h;
    message = message_text;

    text_texture = loadFont(renderer, font_path, font_size, message_text);
}

void TextBox::display(SDL_Renderer* renderer, int x, int y) const {
        
    text_rect.x = x;
    text_rect.y = y;

    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
    
}

SDL_Texture* TextBox::loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string message_text) {

    TTF_Font* font = TTF_OpenFont(font_path.c_str(), 24);

    if (!font) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "TTF: Failed to load font\n", NULL);
        exit(2);
    }

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message_text.c_str(), White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_FreeSurface(surfaceMessage);

    return Message;
}




