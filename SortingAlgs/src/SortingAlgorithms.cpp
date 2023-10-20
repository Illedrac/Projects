#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include <random>
#include <unordered_set>
#include <vector>

// Override base class with your custom functionality
class SortingAlgorithms : public olc::PixelGameEngine
{
public:
    SortingAlgorithms()
    {
        // Name your application
        sAppName = "Sorting Algorithms";
    }

    bool OnUserCreate() override
    {
        maxNumbers = ScreenHeight();
        unsortedNumbersVec.resize(0);

        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, maxNumbers);
    
        while (unsortedNumbers.size() < maxNumbers) {
            int curNum = distrib(gen);

            if (unsortedNumbers.find(curNum) == unsortedNumbers.end()) {
                unsortedNumbers.insert(curNum);
                unsortedNumbersVec.push_back(curNum);
            }
        }

        std::sort(unsortedNumbersVec.begin(), unsortedNumbersVec.end());

        for (int i = 0; i < unsortedNumbersVec.size(); i++) {
            std::cout << unsortedNumbersVec.at(i) << " ";
        }

        std::cout << "END";

        // for each x ->
        // loop from ScreenHeight() -> current unsortedNumbers value
        // draw(x,y, white)

        for (int x = 0; x < ScreenWidth(); x++) {
            for (int y = 0; y < unsortedNumbersVec.at(x%(maxNumbers-1)) ; y++) {
                Draw(x, y, olc::Pixel(255, 255, 255));
                //std::cout << "X: " << x << " Y: " << y << " UNSORT: " << unsortedNumbersVec.at(x) << " UNSORT - MAX: " << maxNumbers - unsortedNumbersVec.at(x) << std::endl;
            }
        }
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;
        
        return true;
    }

private:
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen; // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib;

    std::unordered_set<int> unsortedNumbers;
    int maxNumbers;
    std::vector<int> unsortedNumbersVec;
};



int main() {

    SortingAlgorithms sA;
    sA.Construct(1920, 1080, 4, 4,true);
    sA.Start();

    

    return 0;
}