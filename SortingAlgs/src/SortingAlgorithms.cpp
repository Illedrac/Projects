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

        //DrawArray();
        DrawColorfullArray();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;

        if (GetKey(olc::Key::SPACE).bPressed)
            shouldContinue = !shouldContinue;
        
        //std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
        if (shouldContinue) {
            runBubbleSort();
            //runInsertionSort();
        }
            
        //}
        //DrawArray();

        return true;
    }

    // needs to start as curI = 1 curJ = 0
    void runInsertionSort() {
        if (startSort) {
            curI = 1;
            curJ = curI - 1;
            insertionSortTempValue = unsortedNumbersArr[curI];
            startSort = false;
        }
        

        if (curI < unsortedNumbersArrSize) {        // for curI = 1; i 
            if (curJ >= 0 && unsortedNumbersArr[curJ] > insertionSortTempValue) {
                unsortedNumbersArr[curJ + 1] = unsortedNumbersArr[curJ];
                //DrawArray(curJ + 1);
                //DrawArray(curJ);
                DrawColorfullArray(curJ + 1);
                DrawColorfullArray(curJ);

                curJ--;
            }
            else {
                unsortedNumbersArr[curJ + 1] = insertionSortTempValue;
                //DrawArray(curJ + 1);
                DrawColorfullArray(curJ + 1);
                curI++;
                insertionSortTempValue = unsortedNumbersArr[curI];
                curJ = curI - 1;
            }
           
        }
    }
    
    //needs to start as curI == curJ == 0
    void runBubbleSort() {
        if (curI < unsortedNumbersArrSize) {
            if (curJ < unsortedNumbersArrSize) {
                bubbleSort();
                curJ++;
            }
            else if (curJ >= unsortedNumbersArrSize) {
                curI++;
                curJ = curI + 1;
                bubbleSort();
            }
        }
    }

    void bubbleSort() {

        if (curI < unsortedNumbersArrSize) {

            if (unsortedNumbersArr[curJ] < unsortedNumbersArr[curI]) {
                int temp = unsortedNumbersArr[curI];
                unsortedNumbersArr[curI] = unsortedNumbersArr[curJ];
                unsortedNumbersArr[curJ] = temp;

                //DrawArray(curI);
                //DrawArray(curJ);
                DrawColorfullArray(curI);
                DrawColorfullArray(curJ);

            }
        }
    }

    void DrawColorfullArray(int x) {
        //DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x], olc::Pixel(255%unsortedNumbersArr[x], unsortedNumbersArr[x]*2 % 255, unsortedNumbersArr[x]*3 % 255));
        DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x], unsortedNumbersArrColors[x]);
        DrawLine(x, maxNumberValue - unsortedNumbersArr[x], x, 0, olc::BLACK);
    }

    void DrawColorfullArray() {
        FillRect(0, 0, ScreenHeight(), ScreenWidth(), olc::BLACK);
        for (int x = 0; x < SCREEN_WIDTH_HEIGHT; x++) {
            //DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x], olc::Pixel(unsortedNumbersArr[x] % 255, unsortedNumbersArr[x]*2 % 255, unsortedNumbersArr[x]*3 % 255));
            DrawLine(x, SCREEN_WIDTH_HEIGHT, x, maxNumberValue - unsortedNumbersArr[x], unsortedNumbersArrColors[x]);
        }
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
    
    void createUnsortedArray() {
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, maxNumberValue);

        unsortedNumbers.clear();
        unsortedNumbersArrSize = (sizeof(unsortedNumbersArr) / sizeof(int));

        int index = 0;
        while (unsortedNumbers.size() < maxNumbers) {
            if (updateRGB) {
                updateRGB = false;
                if (b <= 255 && r >= 1 && g >= 1) {

                    if (r < 255 && b == 1) r++;
                    if (g < 255 && r >= 254 && b <= 2) g++;
                    if (b < 255 && g >= 254) { b++; r--; }
                    if (r <= 2 && b >= 254) { g--; }
                }
            }
            else {
                updateRGB = true;
            }

            int curNum = distrib(gen);

            if (unsortedNumbers.find(curNum) == unsortedNumbers.end()) {
                unsortedNumbers.insert(curNum);
                unsortedNumbersArr[index] = curNum;
                unsortedNumbersArrColors[index] = olc::Pixel(r, g, b);
                index++;
            }
        }
    }

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen; // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib;

    std::unordered_set<int> unsortedNumbers;

    bool startSort = true;
    bool shouldContinue = false;

    int maxNumberValue;
    int maxNumbers;
    int unsortedNumbersArr[SCREEN_WIDTH_HEIGHT];
    olc::Pixel unsortedNumbersArrColors[SCREEN_WIDTH_HEIGHT];
    int unsortedNumbersArrSize;
    int curI = 0;
    int curJ = 0;
    int insertionSortTempValue;
    int r = 255;
    int g = 40;
    int b = 1;
    bool updateRGB = true;

};





int main() {

    SortingAlgorithms sA;
    sA.Construct(SCREEN_WIDTH_HEIGHT,SCREEN_WIDTH_HEIGHT, 2, 2);
    sA.Start();

    int i = 0, j = 0;

    //std::future<void> fut = std::async(std::launch::async, [&] { sA.DrawArray(i, sA.unsortedNumbersArr[j)); }, i, sA.unsortedNumbersArr[j));


    return 0;
}