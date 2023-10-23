#include <iostream>
#include "InsertionSort.h"

InsertionSort::InsertionSort():
    insertionSortTempValue(-1)
{
    createUnsortedArray();
}

std::vector<int> InsertionSort::sortArray() {
    // needs to start as curI = 1 curJ = 0
    if (startSort) {
        curI = 1;
        curJ = curI - 1;
        insertionSortTempValue = unsortedNumbersArray[curI];
        startSort = false;
    }

    arrayIndicesToBeDrawn.resize(0);


    if (curI < SCREEN_WIDTH_HEIGHT) {        // for curI = 1; i 
        if (curJ >= 0 && unsortedNumbersArray[curJ] > insertionSortTempValue) {
            unsortedNumbersArray[curJ + 1] = unsortedNumbersArray[curJ];

            arrayIndicesToBeDrawn.push_back(curJ + 1);
            arrayIndicesToBeDrawn.push_back(curJ);

            curJ--;
        }
        else {
            unsortedNumbersArray[curJ + 1] = insertionSortTempValue;

            arrayIndicesToBeDrawn.push_back(curJ + 1);

            curI++;
            insertionSortTempValue = unsortedNumbersArray[curI];
            curJ = curI - 1;
        }

    }

    return arrayIndicesToBeDrawn;
}

