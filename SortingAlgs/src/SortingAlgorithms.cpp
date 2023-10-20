#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include <random>
#include <unordered_set>
#include <vector>
#include <chrono>

void bubbleSort(std::vector<int>& vector);

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
        maxNumberValue = ScreenHeight();
        maxNumbers = ScreenWidth();
        unsortedNumbersVec.resize(0);

        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, maxNumberValue);
    
        while (unsortedNumbers.size() < maxNumbers) {
            int curNum = distrib(gen);

            if (unsortedNumbers.find(curNum) == unsortedNumbers.end()) {
                unsortedNumbers.insert(curNum);
                unsortedNumbersVec.push_back(curNum);
            }
        }

        //std::sort(unsortedNumbersVec.begin(), unsortedNumbersVec.end());

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;

        DrawVector();
        
        if (GetKey(olc::Key::SPACE).bPressed) {
            bubbleSort();
        }
        //DrawVector();

        return true;
    }

    void bubbleSort() {
        for (int i = 0; i < unsortedNumbersVec.size(); i++) {
            for (int j = i + 1; j < unsortedNumbersVec.size(); j++)
            {
                if (unsortedNumbersVec.at(j) < unsortedNumbersVec.at(i)) {
                    int temp = unsortedNumbersVec.at(i);
                    unsortedNumbersVec.at(i) = unsortedNumbersVec.at(j);
                    unsortedNumbersVec.at(j) = temp;
                }
                //std::this_thread::sleep_for(std::chrono::milliseconds{ 2 });
            }
        }
    }

    void DrawVector() {
        for (int x = 0; x < ScreenWidth(); x++) {
            for (int y = ScreenWidth() - 1; y >= 0; y--) {
                if (y > (maxNumberValue - unsortedNumbersVec.at(x)))
                    Draw(x, y, olc::Pixel(255, 255, 255));
                else
                    Draw(x, y, olc::Pixel(0,0,0));
                        
                //std::cout << "X: " << x << " Y: " << y << " UNSORT: " << unsortedNumbersVec.at(x) << " UNSORT - MAX: " << maxNumberValue - unsortedNumbersVec.at(x) << std::endl;
            }
        }
    }

private:
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen; // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib;

    std::unordered_set<int> unsortedNumbers;
    int maxNumberValue;
    int maxNumbers;
    std::vector<int> unsortedNumbersVec;
    bool shouldUpdate = true;
};





int main() {

    SortingAlgorithms sA;
    sA.Construct(1000, 1000, 1, 1);
    sA.Start();

    

    return 0;
}