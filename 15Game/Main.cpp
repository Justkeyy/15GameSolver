#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Solver.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int size_x, size_y;
	cout << "Enter size of board: \n";
	cout << "X width (x <= 4 && x >= 1) = \n";
	cin >> size_x;
	cout << "Y width (y <= 4 && y >= 1)= \n";
	cin >> size_y;

	if (size_x < 1 || size_x > 4)
	{
		cout << "Wrong x width! Exiting the program";
		exit;
	}

	if (size_y < 1 || size_y > 4)
	{
		cout << "Wrong y width! Exiting the program";
		exit;
	}

	{
		vector <int> initbrd(size_x * size_y);

		for (int i = 0; i < (size_x * size_y) - 1; i++)
		{
			initbrd.at(i) = i + 1;
		}

		for (int i = 0; i < (size_x * size_y); i++)
		{
			cout << initbrd.at(i) << " ";
			if ((i + 1) % size_x == 0)
			{
				cout << "\n";
			}
		}

		Solver sol1;
		Solution solution1(Solver::solve(initbrd, size_x, size_y, sol1));
		sol1.PrintSolution(&solution1);
	}

	return 0;
}
