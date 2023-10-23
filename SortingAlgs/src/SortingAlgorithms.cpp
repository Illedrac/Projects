#include "SortingAlgorithms.h"
#include "AlgorithmFactory.h"

// Override base class with your custom functionality

    SortingAlgorithms::SortingAlgorithms()
    {
        // Name your application
        sAppName = "Sorting Algorithms";
    }

    bool SortingAlgorithms::OnUserCreate() 
    {
        return true;
    }

    bool SortingAlgorithms::OnUserUpdate(float fElapsedTime) 
    {
        //DrawStringDecal(olc::vf2d(SCREEN_WIDTH_HEIGHT / 4 - 50, SCREEN_WIDTH_HEIGHT / 4), "Choose a Sorting Algorithm", olc::WHITE, olc::vf2d(1.5,1.5));

        
        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;

        if (GetKey(olc::Key::SPACE).bPressed)
            shouldContinue = !shouldContinue;

        if (sortingAlgorithm == nullptr) {
            sortingAlgorithm = AlgorithmFactory::build(AlgorithmType::INSERTION_SORT);
            //sortingAlgorithm = AlgorithmFactory::build(AlgorithmType::BUBBLE_SORT);
            DrawArray();
        }

        //sortingAlgorithm->sortArray();

        //std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
        if (shouldContinue && sortingAlgorithm->isStillSorting()) {
            std::vector<int> indicesToBeDrawn = sortingAlgorithm->sortArray();
        
            for (int cur : indicesToBeDrawn) {
                DrawArray(cur);
            }
        }
               

        return true;
    }

    void SortingAlgorithms::DrawColorfullArray(int x) {
        //DrawLine(x, SCREEN_WIDTH_HEIGHT, x, SCREEN_WIDTH_HEIGHT - unsortedNumbersArr[x], olc::Pixel(255%unsortedNumbersArr[x], unsortedNumbersArr[x]*2 % 255, unsortedNumbersArr[x]*3 % 255));
        std::tuple<int, int, int> colorValues = sortingAlgorithm->getColor(sortingAlgorithm->getUnsortedNumbersArray(x));
        DrawLine(x, SCREEN_WIDTH_HEIGHT, x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x), olc::Pixel(std::get<0>(colorValues), std::get<1>(colorValues), std::get<2>(colorValues)));
        DrawLine(x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x), x, 0, olc::BLACK);
    }

    void SortingAlgorithms::DrawColorfullArray() {
        std::tuple<int, int, int> colorValues;
        FillRect(0, 0, ScreenHeight(), ScreenWidth(), olc::BLACK);
        for (int x = 0; x < SCREEN_WIDTH_HEIGHT; x++) {
            colorValues = sortingAlgorithm->getColor(sortingAlgorithm->getUnsortedNumbersArray(x));
            DrawLine(x, SCREEN_WIDTH_HEIGHT, x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x), olc::Pixel(std::get<0>(colorValues), std::get<1>(colorValues), std::get<2>(colorValues)));
        }
    }

    void SortingAlgorithms::DrawArray(int x) {
        if (printColorful) {
            DrawColorfullArray(x);
        }
        else {
            DrawLine(x, SCREEN_WIDTH_HEIGHT, x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x));
            DrawLine(x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x), x, 0, olc::BLACK);
        }
    }
        
    void SortingAlgorithms::DrawArray() {
        if (printColorful) {
            DrawColorfullArray();
        }
        else {
            FillRect(0, 0, ScreenHeight(), ScreenWidth(), olc::BLACK);
            for (int x = 0; x < SCREEN_WIDTH_HEIGHT; x++) {
                DrawLine(x, SCREEN_WIDTH_HEIGHT, x, SCREEN_WIDTH_HEIGHT - sortingAlgorithm->getUnsortedNumbersArray(x));
            }
        }
    }






int main() {

    SortingAlgorithms sA;
    sA.Construct(SCREEN_WIDTH_HEIGHT, SCREEN_WIDTH_HEIGHT, 1,1);
    sA.Start();

    return 0;
}