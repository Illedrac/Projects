#pragma once
#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#endif
#include <iostream>

class AlgorithmFactory;
class Algorithm;
enum AlgorithmType;


#define SCREEN_WIDTH_HEIGHT 500

class AlgorithmFactory;

// Override base class with your custom functionality
class SortingAlgorithms : public olc::PixelGameEngine
{
public:
    SortingAlgorithms();

    
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;
    /*
    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        //DrawStringDecal(olc::vf2d(SCREEN_WIDTH_HEIGHT / 4 - 50, SCREEN_WIDTH_HEIGHT / 4), "Choose a Sorting Algorithm", olc::WHITE, olc::vf2d(1.5,1.5));


        if (GetKey(olc::Key::ESCAPE).bPressed)
            return false;

        if (GetKey(olc::Key::SPACE).bPressed)
            shouldContinue = !shouldContinue;

        if (sortingAlgorithm == nullptr) {
            sortingAlgorithm = AlgorithmFactory::build(AlgorithmType::INSERTION_SORT);
            DrawArray();
        }

        //sortingAlgorithm->sortArray();

        //std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
        if (shouldContinue) {
            //sortingAlgorithm->sortArray();
        }

        return true;
    }*/


    void DrawColorfullArray(int x);

    void DrawColorfullArray();

    void DrawArray(int x);

    void DrawArray();



    bool shouldContinue = false;
    bool printColorful = true;

    olc::Pixel unsortedNumbersArrColors[SCREEN_WIDTH_HEIGHT];
    int unsortedNumbersArrSize;

    int insertionSortTempValue;

    Algorithm* sortingAlgorithm;

};


/*
class SortingAlgorithms : public olc::PixelGameEngine {
public:
    SortingAlgorithms();
    void DrawColorfullArray(int x);

    void DrawColorfullArray();

    void DrawArray(int x);

    void DrawArray();


    bool shouldContinue = false;
    bool printColorful = false;

    olc::Pixel unsortedNumbersArrColors[SCREEN_WIDTH_HEIGHT];
    int unsortedNumbersArrSize;

    int insertionSortTempValue;

    Algorithm* sortingAlgorithm;

};
*/
