#include "Solver.h"
#include <vector>
//#define debug

Solver::Solver()
{
	GoalBoard = nullptr;
	Openlist = new Solution;
	Closedlist = new Solution;
	Waylist = new Solution;
}

// Методы 

std::vector<int>* Solver::debuging(const int X_width, const int Y_width) // this is for debugging
{
	std::vector <int>* debbrd = new std::vector <int>;
	debbrd->resize(X_width * Y_width);

	/*debbrd->at(0) = 3;
	debbrd->at(1) = 0;
	debbrd->at(2) = 2;
	debbrd->at(3) = 1;*/

	/*debbrd->at(0) = 1;
	debbrd->at(1) = 2;
	debbrd->at(2) = 3;
	debbrd->at(3) = 4;
	debbrd->at(4) = 5;
	debbrd->at(5) = 0;
	debbrd->at(6) = 6;
	debbrd->at(7) = 7;
	debbrd->at(8) = 8;*/

	/*debbrd->at(0) = 1;
	debbrd->at(1) = 2;
	debbrd->at(2) = 3;
	debbrd->at(3) = 4;
	debbrd->at(4) = 5;
	debbrd->at(5) = 0;
	debbrd->at(6) = 7;
	debbrd->at(7) = 8;
	debbrd->at(8) = 6;*/

	debbrd->at(0) = 0;
	debbrd->at(1) = 2;
	debbrd->at(2) = 5;
	debbrd->at(3) = 1;
	debbrd->at(4) = 3;
	debbrd->at(5) = 4;

	return debbrd;
}

board* Solver::LeftNeighbour(board* pointer, board* OpenP, Solver* solution)
{
	std::swap(pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x),
	pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x - 1));
	pointer->zero_x = pointer->zero_x - 1;
	pointer->manhatten = pointer->manhattan(*solution->GoalBoard);
	return pointer;
}

board* Solver::RightNeighbour(board* pointer, board* OpenP, Solver* solution)
{
	std::swap(pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x),
	pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x + 1));
	pointer->zero_x = pointer->zero_x + 1;
	pointer->manhatten = pointer->manhattan(*solution->GoalBoard);
	return pointer;
}

board* Solver::UpNeighbour(board* pointer, board* OpenP, Solver* solution)
{
	std::swap(pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x),
	pointer->board_field.at((pointer->zero_y - 1) * pointer->size_x + pointer->zero_x));
	pointer->zero_y = pointer->zero_y - 1;
	pointer->manhatten = pointer->manhattan(*solution->GoalBoard);
	return pointer;
}

board* Solver::DownNeighbour(board* pointer, board* OpenP, Solver* solution)
{
	std::swap(pointer->board_field.at(pointer->zero_y * pointer->size_x + pointer->zero_x),
	pointer->board_field.at((pointer->zero_y + 1) * pointer->size_x + pointer->zero_x));
	pointer->zero_y = pointer->zero_y + 1;
	pointer->manhatten = pointer->manhattan(*solution->GoalBoard);
	return pointer;
}

void Solver::NeighbourFound(board* OpenP, board* PLeft, board* PRight, board* PDown, board* PUp)
{
	if (OpenP->zero_y == OpenP->size_y - 1) // lower edge
	{
		if (OpenP->zero_x == OpenP->size_x - 1) // right lower corner
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PUp = this->UpNeighbour(PUp,  OpenP, this);
			//////////////////////////////////////////////////////////
			delete PDown;
			delete PUp;
		}

		else if (OpenP->zero_x == 0) // left lower corner
		{
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PUp = this->UpNeighbour(PUp, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PLeft;
			delete PDown;
		}

		else // lower midle
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PUp = this->UpNeighbour(PUp, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PDown;
		}

	}

	else if (OpenP->zero_y == 0) // upper edge
	{
		if (OpenP->zero_x == OpenP->size_x - 1) // right upper corner
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PUp;
			delete PRight;
		}

		else if (OpenP->zero_x == 0) // left upper corner
		{
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PUp;
			delete PLeft;
		}

		else // upper midle
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PUp;
		}

	}

	else // left edge + right edge + free position
	{
		if (OpenP->zero_x == OpenP->size_x - 1) // right edge
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PUp = this->UpNeighbour(PUp, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PRight;
		}

		else if (OpenP->zero_x == 0) // left edge
		{
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PUp = this->UpNeighbour(PUp, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
			/////////////////////////////////////////////////////////
			delete PLeft;
		}

		else // free position
		{
			PLeft = this->LeftNeighbour(PLeft, OpenP, this);
			PRight = this->RightNeighbour(PRight, OpenP, this);
			PUp = this->UpNeighbour(PUp, OpenP, this);
			PDown = this->DownNeighbour(PDown, OpenP, this);
		}
	}

}

void Solver::SetParent(board* PLeft, board* PRight, board* PDown, board* PUp)
{
	if (PRight != nullptr)
	{
		PRight->parent = *this->Closedlist->m_list.begin();
		PRight->depth = PRight->parent->depth + 1;
		std::cout << *PRight << "\n"; // cout all neighbours 
	}
	if (PLeft != nullptr)
	{
		PLeft->parent = *this->Closedlist->m_list.begin();
		PLeft->depth = PLeft->parent->depth + 1;
		std::cout << *PLeft << "\n";
	}
	if (PUp != nullptr)
	{
		PUp->parent = *this->Closedlist->m_list.begin();
		PUp->depth = PUp->parent->depth + 1;
		std::cout << *PUp << "\n";
	}
	if (PDown != nullptr)
	{
		PDown->parent = *this->Closedlist->m_list.begin();
		PDown->depth = PDown->parent->depth + 1;
		std::cout << *PDown << "\n";
	}
}

void Solver::ClosestBoards(board* PLeft, board* PRight, board* PDown, board* PUp)
{
	std::forward_list <board*>::iterator itr = this->Openlist->m_list.begin();
	board* pp; // supportive pointer for search thrue list
	int size = this->Openlist->m_size;

	for (int i = 0; i < size; i++)
	{
		pp = *itr;
		if (PLeft != nullptr && *pp == *PLeft)
		{
			if ((pp->depth) > (PLeft->depth))
			{
				pp->depth = PLeft->depth;
				pp->parent = PLeft->parent;
			}
			delete PLeft;
			PLeft = nullptr;
		}
		if (PRight != nullptr && *pp == *PRight)
		{
			if ((pp->depth) > (PRight->depth))
			{
				pp->depth = PRight->depth;
				pp->parent = PRight->parent;
			}
			delete PRight;
			PRight = nullptr;
		}
		if (PDown != nullptr && *pp == *PDown)
		{
			if ((pp->depth) > (PDown->depth))
			{
				pp->depth = PDown->depth;
				pp->parent = PDown->parent;
			}
			delete PDown;
			PDown = nullptr;
		}
		if (PUp != nullptr && *pp == *PUp)
		{
			if ((pp->depth) > (PUp->depth))
			{
				pp->depth = PUp->depth;
				pp->parent = PUp->parent;
			}
			delete PUp;
			PUp = nullptr;
		}
		itr++;
	}
}

void Solver::FindSimilar(board* PLeft, board* PRight, board* PDown, board* PUp)
{
	std::forward_list <board*>::iterator itr = this->Closedlist->m_list.begin();
	board* pp;
	int size = this->Closedlist->m_size;
	for (int i = 0; i < size; i++)
	{
		pp = *itr;
		if (PLeft != nullptr && *pp == *PLeft)
		{
			delete PLeft;
			PLeft = nullptr;
		}
		if (PRight != nullptr && *pp == *PRight)
		{
			delete PRight;
			PRight = nullptr;
		}
		if (PDown != nullptr && *pp == *PDown)
		{
			delete PDown;
			PDown = nullptr;
		}
		if (PUp != nullptr && *pp == *PUp)
		{
			delete PUp;
			PUp = nullptr;
		}
		itr++;
	}

}

void Solver::PutToOpen(board* PLeft, board* PRight, board* PDown, board* PUp)
{
	if (PLeft)
	{
		this->Openlist->m_list.push_front(PLeft);
		this->Openlist->m_size++;
	}
	if (PRight)
	{
		this->Openlist->m_list.push_front(PRight);
		this->Openlist->m_size++;
	}
	if (PUp)
	{
		this->Openlist->m_list.push_front(PUp);
		this->Openlist->m_size++;
	}
	if (PDown)
	{
		this->Openlist->m_list.push_front(PDown);
		this->Openlist->m_size++;
	}
}

Solution Solver::solve(std::vector <int> InitialDesk, const int X_width, const int Y_width, Solver solution)
{
	////////////////////////////////////////////////// Set goal board
	solution.GoalBoard = new board(InitialDesk, X_width, Y_width);
	////////////////////////////////////////////////////////////////////////
#ifdef debug // for debuging 
	board* Initial = new board(*solution.debuging(X_width, Y_width), X_width, Y_width);
#else
	////////////////////////////////////////////////////////////////////////
	board* Initial = new board(InitialDesk, X_width, Y_width);
	board::create_random(*Initial);
#endif
	////////////////////////////////////////////////// Add random board to open list as a start position
	if (Initial->is_solvable())
	{
		solution.Openlist->m_list.push_front(Initial);
		solution.Openlist->m_size++;
		bool IsSolution = false; // search over flag
		board* OpenP = *(solution.Openlist->m_list.begin()); // current board pointer
		OpenP->manhatten = OpenP->manhattan(*solution.GoalBoard);
		board* PLeft = nullptr; // neighboring boards pointers
		board* PRight = nullptr;
		board* PDown = nullptr;
		board* PUp = nullptr;
		int moves = 0; // moves counter

		std::cout<< " \n Целевая доска: \n" << *solution.GoalBoard << "\n";

		if (*OpenP == *solution.GoalBoard) // check if start board is already solved
		{
			std::cout << "Solution found!" << "\n";
			solution.Waylist->m_list.push_front(OpenP);
			IsSolution = true;
			return *solution.Waylist;
		}
		else
		{
			do
			{
				moves++;
				std::cout << "\n" << moves << "\n"; // cout current moves and board
				std::cout << *OpenP << "\n";

				PLeft = new board(*OpenP); 
				PRight = new board(*OpenP);
				PDown = new board(*OpenP);
				PUp = new board(*OpenP);

				solution.NeighbourFound(OpenP, PLeft, PRight, PDown,  PUp); // locking fo neighbour boards

				if (PLeft->board_field.empty())
				{
					PLeft = nullptr;
				}

				if (PRight->board_field.empty())
				{
					PRight = nullptr;
				}

				if (PDown->board_field.empty())
				{
					PDown = nullptr;
				}

				if (PUp->board_field.empty())
				{
					PUp = nullptr;
				}

				//////////////////////////////////////////////////////////////////////////////////
				solution.Closedlist->m_list.push_front(OpenP); // After finding neighboring boards - put the start position in closed list
				solution.Closedlist->m_size++;
				solution.Openlist->m_list.remove(OpenP);
				solution.Openlist->m_size--;

				solution.SetParent(PLeft, PRight, PDown, PUp); // setting parrent poin for each point found

				std::cout << "\n" << "//////////////////////////////////////////////////////////////////" << "\n";

				////////////////////////////////////////////////////////////////////////////////////

				if (!solution.Openlist->m_list.empty())
				{
					solution.ClosestBoards(PLeft, PRight, PDown, PUp); // Boards checking (Which point is closest?)
				}

				if (PLeft && PLeft->board_field.empty())
				{
					PLeft = nullptr;
				}

				if (PRight && PRight->board_field.empty())
				{
					PRight = nullptr;
				}

				if (PDown && PDown->board_field.empty())
				{
					PDown = nullptr;
				}

				if (PUp && PUp->board_field.empty())
				{
					PUp = nullptr;
				}

				solution.FindSimilar(PLeft, PRight, PDown, PUp); // Checking for similar points in closed list

				if (PLeft && PLeft->board_field.empty())
				{
					PLeft = nullptr;
				}

				if (PRight && PRight->board_field.empty())
				{
					PRight = nullptr;
				}

				if (PDown && PDown->board_field.empty())
				{
					PDown = nullptr;
				}

				if (PUp && PUp->board_field.empty())
				{
					PUp = nullptr;
				}

				////////////////////////////////////////////////////////////////////////////////////

				solution.PutToOpen(PLeft, PRight, PDown, PUp); // Puting all points that have been found in open list
			
				///////////////////////////////////////////// Looking for point with best heuristics

				std::forward_list <board*>::iterator itr = solution.Openlist->m_list.begin();
				board* pp;
				board* BestBoard = *itr;
				
				for (int i = 0; i < solution.Openlist->m_size; i++)
				{
					pp = *itr;
					if ((BestBoard->manhatten + BestBoard->depth) >(pp->manhatten + pp->depth))
					{
						BestBoard = pp;
					}

					if (*BestBoard == *solution.GoalBoard) // Checking for equality to goal board
					{
						std::cout << "Solution found!" << "\n";
						std::cout << "Size of open list: " << "\n";
						std::cout << solution.Openlist->m_size << "\n";
						board* ppend = pp;
						do
						{
							solution.Waylist->m_list.push_front(ppend);
							solution.Waylist->m_size++;
							ppend = ppend->parent;
						} while (ppend != nullptr);
						IsSolution = true;
						return *solution.Waylist;         // If last board is goal - making way list
					}
					itr++;
				}

				if (solution.Openlist->m_size == 0) // If there is no more moves - wrong solveble checking
				{
					std::cout << "There is no more moves!" << "\n";
					return *solution.Waylist;
				}

				OpenP = BestBoard;

				} while (!IsSolution);
			}
		}
	else
	{
		std::cout << *Initial << "\n";
		std::cout << "There is no solution!" << "\n";
		return *solution.Waylist;
	}

}

void Solver::PrintSolution(Solution* sol)
{
	sol->moves();
	std::forward_list <board*>::iterator itr = sol->m_list.begin();
	board* pp;
	for (int i = 0; i < sol->m_size; i++)
	{
		pp = *itr;
		std::cout << *pp << "\n";
		itr++;
	}
}