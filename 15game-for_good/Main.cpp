#include <cstdlib>
#include <iostream>
#include <tchar.h>
#include <vector>

#include "Initializer.h"
#include "Solver.h"
#include "SimpleTimer.h"

int _tmain(int argc, _TCHAR *argv[])
{
    int size_x, size_y; // size of board
    {
        std::vector<int> initbrd;
        try
        {
            initbrd = initializer(size_x, size_y); // init brd
        }
        catch (int er)
        {
            if (er == 12)
            {
                std::cout << "Wrong x width! Exiting the program";
                return 0;
            }

            if (er == 13)
            {
                std::cout << "Wrong y width! Exiting the program";
                return 0;
            }
        }

//        SimpleTimer st;

        {
            Solver sol1;
            board brd1(initbrd, size_x, size_y);
            Solution solution1 = sol1.solve(brd1);
            std::cout << solution1;
        }
    }

    return 0;
}
