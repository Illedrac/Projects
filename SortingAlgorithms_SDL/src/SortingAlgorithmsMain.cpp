#include <algorithm>
#undef main

#include "SortingAlgorithmsMain.h"

SortingAlgorithmsMain::SortingAlgorithmsMain(SDL_Window* window, SDL_Renderer* renderer) : 
    window(window), 
    renderer(renderer)
{}

SortingAlgorithmsMain::SortingAlgorithmsMain(int screen_width, int height) :
    window(nullptr),
    renderer(nullptr),
    sorting_algorithm_implementation(),
    text_boxes_vector()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(screen_width, height, 0, &window, &renderer);
}

std::string SortingAlgorithmsMain::GetFontPath(const std::string& font_name){
    std::string path_to_font = SDL_GetBasePath();
    path_to_font = path_to_font.substr(2, path_to_font.size() - 1);
    std::replace(path_to_font.begin(), path_to_font.end(), '\\', '/');
    path_to_font.append("../Resources/");
    path_to_font.append(font_name);

    return path_to_font;
}

void SortingAlgorithmsMain::DisplayTextBoxes(int screen_width) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int offset = 30;
    for (int i = 0; i < text_boxes_vector.size(); i++) {
        TextBox* cur = text_boxes_vector.at(i);

        if (i == 0) {
            //Title
            cur->display(renderer, 0, 0);
        }
        else {
            //Folowing Text Boxes
            cur->display(renderer,
                         (screen_width / 2) - (cur->text_rect.w / 2),
                         text_boxes_vector.at(i - 1)->text_rect.y + text_boxes_vector.at(i - 1)->text_rect.h + offset
                         );
        }
    }
    SDL_RenderPresent(renderer);
}

void SortingAlgorithmsMain::SetAlgorithmType(AlgorithmType algorithm_type, int screen_width) {
    int unsorted_array_size = screen_width / 2;
    sorting_algorithm_implementation = AlgorithmFactory::CreateAlgorithm(algorithm_type, screen_width, unsorted_array_size);
}


void SortingAlgorithmsMain::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SortingAlgorithmsMain::DrawInitialArray(int screen_width) {
   
    sorting_algorithm_implementation->DrawCurrentArray(window, renderer, screen_width);
    
    // swap and display buffer
    SDL_RenderPresent(renderer);
}

void SortingAlgorithmsMain::Initialize(int screen_width) {
    //Error Check
    if (window == nullptr || renderer == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window or Renderer are Null", NULL);
    }


    std::string path_to_font = GetFontPath("arial.ttf");
    int text_box_width = screen_width;
    int text_box_height = 100;
    text_boxes_vector.clear();

    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 35, text_box_width, text_box_height, "Sorting Algorithm Visualizer"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width/2, text_box_height/3, "Choose A Sorting Algorithm"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height , "Insertion Sort"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height, "Binary Insertion Sort"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height, "Selection Sort"));
}

int WinMain() {

    int screen_width = 1000;
    const int FPS = 60, frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int frame_time;

    SortingAlgorithmsMain* sAM = new SortingAlgorithmsMain(screen_width, screen_width);
    sAM->Initialize(screen_width);

    SDL_Event event;
    bool continue_running_program = SDL_TRUE;
    bool full_screen = false;
    bool display_initial_array = true;
    bool main_menu = true;
    
    while (continue_running_program) {

            frame_start = SDL_GetTicks();
            

        // Check if this while loop causes an error
        while (SDL_PollEvent(&event)) {
            

            if (main_menu){
                sAM->DisplayTextBoxes(screen_width);
                int mouse_x, mouse_y;
                switch (event.type) {
                    case SDL_QUIT:
                        TTF_Quit();
                        continue_running_program = SDL_FALSE;
                        break;
                    
                    case SDL_MOUSEMOTION:
                        break;
                    
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                                                        
                            for (int i = 2; i < sAM->text_boxes_vector.size(); i++) {
                                TextBox* current_text_box = sAM->text_boxes_vector.at(i);
                                SDL_GetMouseState(&mouse_x, &mouse_y);
                                
                                if (mouse_x >= current_text_box->text_rect.x && mouse_x <= (current_text_box->text_rect.x + current_text_box->text_rect.w)) {
                                    if (mouse_y >= current_text_box->text_rect.y && mouse_y <= (current_text_box->text_rect.y + current_text_box->text_rect.h)) {
                                        if (current_text_box->message == "Insertion Sort") {
                                            sAM->SetAlgorithmType(AlgorithmType::INSERTION_SORT, screen_width);
                                        }
                                        else if (current_text_box->message == "Binary Insertion Sort") {
                                            sAM->SetAlgorithmType(AlgorithmType::BINARY_INSERTION_SORT, screen_width);
                                        }
                                        else if (current_text_box->message == "Selection Sort") {
                                            sAM->SetAlgorithmType(AlgorithmType::SELECTION_SORT, screen_width);
                                        }
                                        main_menu = false;
                                    }
                                }

                            }
                        }
                        break;
                }
                
                sAM->DisplayTextBoxes(screen_width);
                

            }
            else {

                if (display_initial_array) {
                    sAM->DrawInitialArray(screen_width);
                    display_initial_array = false;
                }

                switch (event.type) {
                case SDL_QUIT:
                    continue_running_program = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                        full_screen = !full_screen;
                        if (full_screen) {
                            SDL_SetWindowFullscreen(sAM->window, SDL_WINDOW_FULLSCREEN);
                        }
                        else {
                            SDL_SetWindowFullscreen(sAM->window, 0);
                        }
                        break;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                        continue_running_program = sAM->sorting_algorithm_implementation->SortArray(sAM->window, sAM->renderer);
                        break;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        continue_running_program = SDL_FALSE;
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        
        if (sAM->sorting_algorithm_implementation && sAM->sorting_algorithm_implementation->isSorted) {
            main_menu = true;
            sAM->sorting_algorithm_implementation = nullptr;
            SDL_SetRenderDrawColor(sAM->renderer, 0, 0, 0, 255);
            SDL_RenderClear(sAM->renderer);
            display_initial_array = true;
        }

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }


    }



   
    
    return 0;
}