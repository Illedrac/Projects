#include "ScoreBoard.h"


ScoreBoard::ScoreBoard(std::string path_to_font)
    :
    text_texture(nullptr),
    text_rect(),
    font()
 
{
    if (TTF_Init() == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to Initialize TTF", NULL);
        exit(2);
    }

    LoadFont(path_to_font, 28);

    text_rect.x = 15;
    text_rect.y = 150;
    text_rect.w = 385;
    text_rect.h = 125;
}


void ScoreBoard::LoadFont(const std::string& font_path, 
                                  const int font_size) 
{
    
    font = TTF_OpenFont((font_path + ".ttf").c_str(), font_size);

    if (!font) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "TTF: Failed to load font\n", NULL);
        exit(2);
    }
}

void ScoreBoard::DisplayScore(SDL_Renderer* renderer, 
                              const int score)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &text_rect);

    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ("Score: " + std::to_string(score * 10)).c_str(), White);

    // now you can convert it into a texture
    text_texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_FreeSurface(surfaceMessage);

    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
    SDL_RenderPresent(renderer);
    
}

void ScoreBoard::DisplayGameOver(SDL_Renderer* renderer,
                                 int last_score,
                                 int screen_width_px,
                                 int screen_height_px)
{


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &text_rect);

    SDL_Color White = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, std::string("GAME OVER").c_str(), White);

    // now you can convert it into a texture
    text_texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int width = 1000;
    int height = 250;

    SDL_Rect game_over_rect;
    game_over_rect.x = screen_width_px / 2 - width / 2;
    game_over_rect.y = screen_height_px / 2 - 2 * height ;
    game_over_rect.h = height;
    game_over_rect.w = width;
    

    SDL_RenderCopy(renderer, text_texture, nullptr, &game_over_rect);
   
    surfaceMessage = TTF_RenderText_Solid(font, ("YOUR SCORE : " + std::to_string(last_score * 10)).c_str(), White);

    // now you can convert it into a texture
    text_texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_FreeSurface(surfaceMessage);

    game_over_rect.x -= 200;
    game_over_rect.y += 400;
    game_over_rect.w += 400;
    game_over_rect.h -= 100;
    
    SDL_RenderCopy(renderer, text_texture, nullptr, &game_over_rect);
    
    surfaceMessage = TTF_RenderText_Solid(font, std::string("Press 'r' to Restart").c_str(), White);

    // now you can convert it into a texture
    text_texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_FreeSurface(surfaceMessage);

    game_over_rect.x -= 50;
    game_over_rect.y += 300;
    game_over_rect.w += 100;
    
    SDL_RenderCopy(renderer, text_texture, nullptr, &game_over_rect);



    SDL_RenderPresent(renderer);
}