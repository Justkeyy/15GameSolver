#include <tchar.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Solver.h"

int main(int argc, char **argv)
{
    std::srand(std::time(nullptr));
    int size_x, size_y;
    std::cout << "Enter size of board: \n";
    std::cout << "X width (x < 4 && x >= 1) = \n";
    std::cin >> size_x;
    std::cout << "Y width (y < 4 && y >= 1)= \n";
    std::cin >> size_y;

    if (size_x < 0)
    {
        size_x = 1;
    }
    else if (size_x > 4)
    {
        size_x = 4;
    }

    if (size_y < 0)
    {
        size_y = 1;
    }
    else if (size_y > 4)
    {
        size_y = 4;
    }

    int **pp = new int *[size_y];
    for (int i = 0; i < size_y; i++)
    {
        pp[i] = new int[size_x];
    }

    int count = 1;

    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            pp[i][j] = count;
            count++;
        }
    }
    pp[size_y - 1][size_x - 1] = 0;

    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            std::cout << pp[i][j] << " ";
        }
        std::cout << "\n";
    }

    {
        Solver sol1;
        Solution solution1(Solver::solve(pp, size_x, size_y, sol1));
        sol1.PrintSolution(&solution1);
    }

    for (int i = 0; i < size_y; i++)
    {
        delete[] pp[i];
    }
    delete[] pp;

    return 0;
}
