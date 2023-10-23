#include "Algorithm.h"

class BubbleSort : public Algorithm {
public:
    BubbleSort();
    
    //needs to start as curI == curJ == 0
    std::vector<int> sortArray();

    void bubbleSort();
};