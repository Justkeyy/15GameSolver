#include "Initializer.h"

std::vector<int> initializer(int &x, int &y)
{
    std::cout << "Enter size of board: \n";
    std::cout << "X width (x <= 4 && x >= 1) = \n";
    std::cin >> x;
    std::cout << "Y width (y <= 4 && y >= 1)= \n";
    std::cin >> y;

    if ((x < 1 || x > 4))
    {
        throw(12);
    }

    if (y < 1 || y > 4)
    {
        throw(13);
    }

    std::vector<int> initbrd(x * y);

    for (int i = 0; i < (x * y) - 1; i++)
    {
        initbrd[i] = i + 1;
    }

    std::cout << "Goal board" << "\n";

    for (int i = 0; i < (x * y); i++)
    {
        std::cout << std::setfill('0') << std::setw(3) << initbrd[i] << " ";
        if ((i + 1) % x == 0)
        {
            std::cout << "\n";
        }
    }

    return initbrd;
}
