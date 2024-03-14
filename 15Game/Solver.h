#pragma once
#include "Solution.h"
#include "Board.h"

class Solver
{
	board* GoalBoard;
	Solution* Openlist;
	Solution* Closedlist;
	Solution* Waylist;

	public:
	Solver();
	~Solver() = default;

	board* LeftNeighbour(board* pointer, board* OpenP, Solver* solution);
	board* RightNeighbour(board* pointer, board* OpenP, Solver* solution);
	board* UpNeighbour(board* pointer, board* OpenP, Solver* solution);
	board* DownNeighbour(board* pointer, board* OpenP, Solver* solution);
	void NeighbourFound(board* OpenP, board* PLeft, board* PRight, board* PDown, board* PUp);
	void SetParent(board* PLeft, board* PRight, board* PDown, board* PUp);
	void ClosestBoards(board* PLeft, board* PRight, board* PDown, board* PUp);
	void FindSimilar(board* PLeft, board* PRight, board* PDown, board* PUp);
	void PutToOpen(board* PLeft, board* PRight, board* PDown, board* PUp);
	static Solution solve(std::vector <int> InitialDesk, const int X_width, const int Y_width, Solver solution);
	std::vector<int>* debuging(const int X_width, const int Y_width);
	void PrintSolution(Solution * sol);

};