#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include <random>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <future>

#define SCREEN_WIDTH_HEIGHT 500

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
        maxNumberValue = SCREEN_WIDTH_HEIGHT;
        maxNumbers = SCREEN_WIDTH_HEIGHT;

        createUnsortedArray();

        DrawArray();

        return true;
    }

    void createUnsortedArray() {
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, maxNumberValue);

        unsortedNumbers.clear();
        unsortedNumbersArrSize = (sizeof(unsortedNumbersArr) / sizeof(int));

        int index = 0;
        while (unsortedNumbers.size() < maxNumbers) {
            int curNum = distrib(gen);

            if (unsortedNumbers.find(curNum) == unsortedNumbers.end()) {
                unsortedNumbers.insert(curNum);
                unsortedNumbersArr[index] = curNum;
                index++;
            }
        }
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;

        bubbleSort();

            
        //}
        //DrawArray();

        return true;
    }

    void bubbleSort() {
        if (curI < unsortedNumbersArrSize) {
            if (curJ < unsortedNumbersArrSize) {
                bubbleSort(curI, curJ);
                curJ++;
            }
            else if (curJ >= unsortedNumbersArrSize) {
                curI++;
                curJ = curI + 1;
                bubbleSort(curI, curJ);
            }
        }
    }

    void bubbleSort(int i, int j) {

        if (i < unsortedNumbersArrSize) {

            if (unsortedNumbersArr[j] < unsortedNumbersArr[i]) {
                int temp = unsortedNumbersArr[i];
                unsortedNumbersArr[i] = unsortedNumbersArr[j];
                unsortedNumbersArr[j] = temp;

                DrawArray(i);
                DrawArray(j);
            }
        }
        /*
        for (int i = 0; i < ( sizeof(unsortedNumbersArr) / sizeof(int) ); i++) {
            for (int j = i + 1; j < ( sizeof(unsortedNumbersArr) / sizeof(int) ); j++)
            {
                if (unsortedNumbersArr[j] < unsortedNumbersArr[i]) {
                    int temp = unsortedNumbersArr[i];
                    unsortedNumbersArr[i] = unsortedNumbersArr[j];
                    unsortedNumbersArr[j] = temp;
                    DrawArray(i, olc::CYAN);
                }
                //std::this_thread::sleep_for(std::chrono::milliseconds{ 2 });
            }
        }
        */
    }

    void DrawArray(int x) {
        DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x]);
        DrawLine(x, maxNumberValue - unsortedNumbersArr[x], x, 0, olc::BLACK);
    }

    void DrawArray(int x, olc::Pixel color) {
        DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x], color);
        DrawLine(x, maxNumberValue - unsortedNumbersArr[x], x, 0, olc::BLACK);
    }
    
    void DrawArray() {
        FillRect(0, 0, ScreenHeight(), ScreenWidth(), olc::BLACK);
        for (int x = 0; x < SCREEN_WIDTH_HEIGHT; x++) {
            DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x] );
        }
    }
    

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen; // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib;

    std::unordered_set<int> unsortedNumbers;
    int maxNumberValue;
    int maxNumbers;
    int unsortedNumbersArr[SCREEN_WIDTH_HEIGHT];
    int unsortedNumbersArrSize;
    bool shouldUpdate = true;
    int curI = 0;
    int curJ = 0;
};





int main() {

    SortingAlgorithms sA;
    sA.Construct(SCREEN_WIDTH_HEIGHT,SCREEN_WIDTH_HEIGHT, 2, 2);
    sA.Start();

    int i = 0, j = 0;

    //std::future<void> fut = std::async(std::launch::async, [&] { sA.DrawArray(i, sA.unsortedNumbersArr[j)); }, i, sA.unsortedNumbersArr[j));


    return 0;
}