#include <algorithm>
#undef main
#include "SortingAlgorithmsMain.h"

// Constructor
// Takes in width and height (Even though it only really works when width = height)
SortingAlgorithmsMain::SortingAlgorithmsMain(int screen_width, int height) :
    window(nullptr),
    renderer(nullptr),
    sorting_algorithm_implementation(),
    text_boxes_vector()
{
    //Init everything for SDL (Not sure why)
    SDL_Init(SDL_INIT_EVERYTHING);
    //Create the window & renderer 
    SDL_CreateWindowAndRenderer(screen_width, height, 0, &window, &renderer);
}

// A function that returns a string to the full path of a given font name
// Based on the SDL_GetBasePath() and uses a resource folder I created to store resources
std::string SortingAlgorithmsMain::GetFontPath(const std::string& font_name){
    std::string path_to_font = SDL_GetBasePath();
    path_to_font = path_to_font.substr(2, path_to_font.size() - 1);
    std::replace(path_to_font.begin(), path_to_font.end(), '\\', '/');
    path_to_font.append("../Resources/");
    path_to_font.append(font_name);

    return path_to_font;
}

// This program uses text boxes as "buttons" -> could refactor to reflect this
// Clear the screen and print out all TextBox objects in the text_boxes_vector
void SortingAlgorithmsMain::DisplayTextBoxes(int screen_width) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int offset = 30;
    for (int i = 0; i < text_boxes_vector.size(); i++) {
        TextBox* cur = text_boxes_vector.at(i);

        // If i == 0 then this is the title, don't have to do any fun logic to determine where to put it
        if (i == 0) {
            cur->display(renderer, 0, 0);
        }
        // Otherwise it's not the title, do some fun logic to determine where it should be drawn
        else {
            cur->display(renderer,
                         (screen_width / 2) - (cur->text_rect.w / 2),
                         text_boxes_vector.at(i - 1)->text_rect.y + text_boxes_vector.at(i - 1)->text_rect.h + offset
                         );
        }
    }
    SDL_RenderPresent(renderer);
}

// Take in an Algorithm type and create the sorting_algorithm_implementation object with the corresponding algorithm
void SortingAlgorithmsMain::SetAlgorithmType(AlgorithmType algorithm_type, int screen_width) {
    // Set the size of the unsorted array
    int unsorted_array_size = screen_width / 10;
    sorting_algorithm_implementation = AlgorithmFactory::CreateAlgorithm(algorithm_type, screen_width, unsorted_array_size);
}

// A function to clear the renderer screen with all black 
void SortingAlgorithmsMain::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

// Used to draw the initial (unsorted) array prior to the user pressing 'r' to run the algorithm
void SortingAlgorithmsMain::DrawInitialArray(int screen_width) {
   
    sorting_algorithm_implementation->DrawInitialArray(window, renderer, screen_width);
    
    // swap and display buffer
    SDL_RenderPresent(renderer);
}

// A function to initialize the main menu 
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
    //text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height, "Binary Insertion Sort"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height, "Selection Sort"));
    text_boxes_vector.push_back(new TextBox(renderer, path_to_font, 15, text_box_width / 2, text_box_height, "Quick Sort"));
}


// Main function
int WinMain() {

    // Screen width in pixels
    int screen_width = 1000;
    // Const variables to control frame rate to 60 FPS
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    // More variables to control frame rate
    Uint32 frame_start;
    int frame_time;

    // Create the main driving object
    SortingAlgorithmsMain* sAM = new SortingAlgorithmsMain(screen_width, screen_width);
    sAM->Initialize(screen_width);

    // Event variable for event handling
    SDL_Event event;
    // Boolean to determine if to continue running the program
    bool continue_running_program = SDL_TRUE;
    // Boolean to determine whether or not to enable full screen -> Doesn't work but that's okay for now
    bool full_screen = false;
    // Boolean to determine whether or not to display the initial (unsorted) array after selecting an algorithm
    bool display_initial_array = true;
    // Boolean to determine whether or not to display the main menus
    bool main_menu = true;
    
    // Main program loop
    while (continue_running_program) {

        frame_start = SDL_GetTicks();
        
        // Loop to drive event handling
        while (SDL_PollEvent(&event)) {
            
            // If we shoudl display the main menu
            if (main_menu){

                // Display the text boxes, we can use the initial array value since we don't have to redraw the menu options
                // unless it's the first frame or we go back to the main menu
                if(display_initial_array) sAM->DisplayTextBoxes(screen_width);
                
                // Variables to store the mouse x & y values
                int mouse_x, mouse_y;

                // Switch statement on the event type 
                switch (event.type) {

                    // Quit if user clicks "X" button
                    case SDL_QUIT:
                        TTF_Quit();
                        continue_running_program = SDL_FALSE;
                        break;
                    
                    // If the user presses a key
                    case SDL_KEYDOWN:
                        
                        // If the user presses 'f', either go into fullscreen or windowed -> doesn't really work :( 
                        if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                            full_screen = !full_screen;
                            if (full_screen) {
                                SDL_SetWindowFullscreen(sAM->window, SDL_WINDOW_FULLSCREEN);
                            }
                            else {
                                SDL_SetWindowFullscreen(sAM->window, 0);
                            }
                        }
                        break;
                    
                    // If the user moves the window, do nothing (?)
                    case SDL_MOUSEMOTION:
                        break;
                    
                    // If the user clicks, check if they clicked a "button"
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            
                            // Could probably do this better but loop over all "buttons" and check if the user clicked that "button"
                            for (int i = 2; i < sAM->text_boxes_vector.size(); i++) {
                                TextBox* current_text_box = sAM->text_boxes_vector.at(i);
                                SDL_GetMouseState(&mouse_x, &mouse_y);
                                
                                // If the user clicks a button, check which button it is, initialize the sorting_algorithm_implementation object with that type of sorting algorithm
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
                                        else if (current_text_box->message == "Quick Sort") {
                                            sAM->SetAlgorithmType(AlgorithmType::QUICK_SORT, screen_width);
                                        }

                                        main_menu = false;
                                    }
                                }

                            }
                        }
                        break;
                }
            }
            // Otherwise, don't display main menu and show the (unsorted) array
            else {

                // If we haven't drawn the (unsorted) array, draw it 
                if (display_initial_array) {
                    sAM->DrawInitialArray(screen_width);
                    display_initial_array = false;
                }

                // Quit if user clicks "X" button
                switch (event.type) {
                case SDL_QUIT:
                    continue_running_program = SDL_FALSE;
                    break;

                // If the user presses a key
                case SDL_KEYDOWN:

                    // Again, if the user presses 'f', either go into fullscreen or windowed -> doesn't really work :( 
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

                    // Otherwise, if the user presses 'r', begin running the sorting algorithm 
                    else if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                        continue_running_program = sAM->sorting_algorithm_implementation->SortArray(sAM->window, sAM->renderer);
                        break;
                    }
                    // Otherwise, if the user presses the ESCAPE key, quit
                    else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        continue_running_program = SDL_FALSE;
                        break;
                    }
                    // 
                    else if (event.key.keysym.scancode == SDL_SCANCODE_M && sAM->sorting_algorithm_implementation && sAM->sorting_algorithm_implementation->isSorted) {
                        main_menu = true;
                        sAM->sorting_algorithm_implementation = nullptr;
                        SDL_SetRenderDrawColor(sAM->renderer, 0, 0, 0, 255);
                        SDL_RenderClear(sAM->renderer);
                        display_initial_array = true;
                        break;
                    }
                    
                default:
                    break;
                }
            }
        }
        
        // If the sorting_algorithm_implementation isn't nullptr and the array has been sorted
        // Then clear the screen and go back to the main menu
       

        // Frame rate variable updating / checking
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }


    }
    
    return 0;
}

/*
// Copy of WinMain for testing
// In regards to coloring current swaps in red, likely need to keep track of the last X index
// With that, when going to draw, update the last index to be colored white, and color the
// Current index in red
int WinMain() {


    std::vector<int> numbers;

    for (int i = 1; i < 250; i++) {
        numbers.push_back(i);
    }



    // Screen width in pixels
    int screen_width = 1000;
    // Const variables to control frame rate to 60 FPS
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    // More variables to control frame rate
    Uint32 frame_start;
    int frame_time;

    // Create the main driving object
    SortingAlgorithmsMain* sAM = new SortingAlgorithmsMain(screen_width, screen_width);
    sAM->Initialize(screen_width);

    // Event variable for event handling
    SDL_Event event;
    // Boolean to determine if to continue running the program
    bool continue_running_program = SDL_TRUE;
    // Boolean to determine whether or not to enable full screen -> Doesn't work but that's okay for now
    bool full_screen = false;
    // Boolean to determine whether or not to display the initial (unsorted) array after selecting an algorithm
    //bool display_initial_array = true;
    // Boolean to determine whether or not to display the main menus
    //bool main_menu = true;
    
    sAM->SetAlgorithmType(AlgorithmType::INSERTION_SORT, screen_width);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->clear();
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(4);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(1);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(9);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(5);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(7);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(2);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(10);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(3);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(6);
    sAM->sorting_algorithm_implementation->unsortedNumbersArray->push_back(8);
    
    sAM->DrawInitialArray(screen_width);


    // Main program loop
    while (continue_running_program) {

        frame_start = SDL_GetTicks();

        // Loop to drive event handling
        while (SDL_PollEvent(&event)) {


            // Quit if user clicks "X" button
            switch (event.type) {
            case SDL_QUIT:
                continue_running_program = SDL_FALSE;
                break;

                // If the user presses a key
            case SDL_KEYDOWN:

                // Otherwise, if the user presses 'r', begin running the sorting algorithm
                if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    continue_running_program = sAM->sorting_algorithm_implementation->SortArray(sAM->window, sAM->renderer);
                    break;
                }
                // Otherwise, if the user presses the ESCAPE key, quit
                else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    continue_running_program = SDL_FALSE;
                    break;
                }
                break;
            default:
                break;
            }

        }

        // Frame rate variable updating / checking
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }


    }
    return 0;
}
*/