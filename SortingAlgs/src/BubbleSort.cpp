#include "BubbleSort.h"

BubbleSort::BubbleSort() 
{
    createUnsortedArray();
}

std::vector<int> BubbleSort::sortArray() {

    arrayIndicesToBeDrawn.resize(0);
    if (curI < SCREEN_WIDTH_HEIGHT) {
        if (curJ < SCREEN_WIDTH_HEIGHT) {
            bubbleSort();
            curJ++;
        }
        else if (curJ >= SCREEN_WIDTH_HEIGHT) {
            curI++;
            curJ = curI + 1;
            bubbleSort();
        }
    }

    return arrayIndicesToBeDrawn;
}

void BubbleSort::bubbleSort() {

    if (curI < SCREEN_WIDTH_HEIGHT) {

        if (unsortedNumbersArray[curJ] < unsortedNumbersArray[curI]) {
            int temp = unsortedNumbersArray[curI];
            unsortedNumbersArray[curI] = unsortedNumbersArray[curJ];
            unsortedNumbersArray[curJ] = temp;

            arrayIndicesToBeDrawn.push_back(curI);
            arrayIndicesToBeDrawn.push_back(curJ);

        }
    }
}
