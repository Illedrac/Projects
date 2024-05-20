#pragma once
#include <memory>
#include <SDL.h>
#include <string>

class GameBoard;
class Snake;
class ButtonHandler;
class ScoreBoard;


const int screen_width_pixels = 1920;
const int screen_height_pixels = 1080;
const int snake_update_delay_ms = 85;
const int FPS = 120;
const int frame_delay = 1000 / FPS;

class GameController {
public:

    GameController();
    ~GameController();

    void StartSnakeGame();

private:

    void GameLoop();
    void DisplayMainMenu();
    void DisplayGame();
    void GameOver();
    void DisplayGameOver();

    std::string GetFontPath(const std::string& font_name);

    std::shared_ptr<GameBoard> game_board_object;
    std::unique_ptr<Snake> snake_object;
    std::unique_ptr<ButtonHandler> button_handler;
    std::unique_ptr<ScoreBoard> score_board;

    // I would've liked these to be unique_ptrs but these
    // don't have deconstructors so unique_ptrs not only don't work
    // but wouldn't actually clean the memory
    SDL_Window* window;
    SDL_Renderer* renderer;

    // More variables to control frame rate
    Uint32 frame_start;
    int frame_time;
    int last_update_made;

    bool continue_running_program;
    bool main_menu;
    bool is_paused;
    bool game_over;

    SDL_Event event;

};