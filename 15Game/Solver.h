#pragma once
#include "Solution.h"

class Solver
{
	board* GoalBoard;
	Solution* Openlist;
	Solution* Closedlist;
	Solution* Waylist;

	public:
	Solver();
	~Solver();
	static Solution solve(int** InitialDesk, const int X_width, const int Y_width, Solver solution);
	void PrintSolution(const Solution * sol) const;

};