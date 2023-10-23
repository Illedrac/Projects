#pragma once 
#include <random>
#include <unordered_set>

#define SCREEN_WIDTH_HEIGHT 500

class SortingAlgorithms;

class Algorithm {
public:

	virtual std::vector<int> sortArray() = 0;

    inline void createUnsortedArray() {
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, SCREEN_WIDTH_HEIGHT);

        unsortedNumbersSet.clear();
        
        GenerateRGB();

        int index = 0;
        while (unsortedNumbersSet.size() < SCREEN_WIDTH_HEIGHT) {
            int curNum = distrib(gen);

            if (unsortedNumbersSet.find(curNum) == unsortedNumbersSet.end()) {
                unsortedNumbersSet.insert(curNum);
                unsortedNumbersArray[index] = curNum;
                index++;
            }
        }
    }

    inline void GenerateRGB() {
        int r = 255;
        int g = 5;
        int b = 5;

        for (int i = 0; i < SCREEN_WIDTH_HEIGHT; i++) {
            if (i >= 0 && i <= (SCREEN_WIDTH_HEIGHT / 4)) {
                g += 2;
                if (g > 255) g = 255;
            }
            else if (i > (SCREEN_WIDTH_HEIGHT / 4) && i < (SCREEN_WIDTH_HEIGHT / 2)) {
                r -= 2;
                if (r < 1) r = 1;
            }
            else if (i > (SCREEN_WIDTH_HEIGHT / 2) && i < (3 * SCREEN_WIDTH_HEIGHT / 4)) {
                b += 2;
                if (b > 255) b = 255;
            }
            else {
                g -= 2;
                if (g < 1) g = 1;
            }
            //std::cout << "I: " << i << " R: " << r << " G: " << g << " B: " << b << std::endl;

            ArrayColors[i] = std::make_tuple(r, g, b);
        }
    }

    inline int getUnsortedNumbersArray(int index) {
        return unsortedNumbersArray[index];
    }

    inline std::tuple<int, int, int> getColor(int index) {
        return ArrayColors[index];
    }

    inline bool isStillSorting() {
        return curI <= SCREEN_WIDTH_HEIGHT;
    }

	int curI = 0;
	int curJ = 0;

	bool startSort = false;

    std::unordered_set<int> unsortedNumbersSet;
	int unsortedNumbersArray[SCREEN_WIDTH_HEIGHT];
    std::tuple<int, int, int> ArrayColors[SCREEN_WIDTH_HEIGHT];
    std::vector<int> arrayIndicesToBeDrawn;

};
