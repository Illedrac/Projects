#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include <thread>
#include <chrono>

// Override base class with your custom functionality
class GameOfLife : public olc::PixelGameEngine
{
public:
    GameOfLife()
    {
        // Name your application
        sAppName = "Game Of Life";
    }

public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        m_output = new int[ScreenWidth() * ScreenHeight()];
        m_state = new int[ScreenWidth() * ScreenHeight()];
        std::memset(m_output, 0, ScreenWidth() * ScreenHeight() * sizeof(int));
        std::memset(m_state, 0, ScreenWidth() * ScreenHeight() * sizeof(int));

        auto set = [&](int x, int y, std::wstring s)
            {
                int p = 0;
                for (auto c : s)
                {
                    m_state[y * ScreenWidth() + x + p] = c == L'#' ? 1 : 0;
                    p++;
                }
            };

        //set(80, 50, L"  #");
        //set(80, 51, L" ###");
        //set(80, 52, L"  #");


        for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
        {
            m_state[i] = rand() % 2;
        }

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });

        if (!GetKey(olc::Key::SPACE).bHeld)
            return true;

        auto cell = [&](int x, int y)
            {
                return m_output[y * ScreenWidth() + x];
            };

        for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
        {
            m_output[i] = m_state[i];
        }

        for (int x = 1; x < ScreenWidth() - 1; x++)
        {
            for (int y = 1; y < ScreenHeight() - 1; y++)
            {
                int nNeighbors = cell(x - 1, y - 1) + cell(x + 0, y - 1) + cell(x + 1, y - 1) +
                    cell(x - 1, y + 0) + 0 + cell(x + 1, y + 0) +
                    cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

                if (cell(x, y) == 1) {
                    m_state[y * ScreenWidth() + x] = nNeighbors == 2 || nNeighbors == 3;
                }
                else
                {
                    m_state[y * ScreenWidth() + x] = nNeighbors == 3;
                }

                if (cell(x, y) == 1)
                {
                    olc::Pixel(255, 255, 255);
                    Draw(x, y, olc::Pixel(255, 255, 255));
                }
                else
                {
                    Draw(x, y, olc::Pixel(0, 0, 0));
                }
            }
        }



        return true;
    }

private:
    int* m_output;
    int* m_state;
};



int main() {

    GameOfLife game;
    game.Construct(320, 200, 4, 4);
    game.Start();
    return 0;
}