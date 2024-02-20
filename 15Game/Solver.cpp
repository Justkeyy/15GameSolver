#include "Solver.h"

//#define debug

// Конструкторы

Solver::Solver()
{
	GoalBoard = nullptr;
	Openlist = new Solution;
	Closedlist = new Solution;
	Waylist = new Solution;
}

Solver::~Solver()
{
	while(Openlist->Head.pNext != &Openlist->Tail)
	{
		delete Openlist->Head.pNext;
	}

	while (Closedlist->Head.pNext != &Closedlist->Tail)
	{
		delete Closedlist->Head.pNext;
	}

	while (Waylist->Head.pNext != &Waylist->Tail)
	{
		delete Waylist->Head.pNext;
	}
}

// Методы 

Solution Solver::solve(int** InitialDesk, const int X_width, const int Y_width, Solver solution)
{
	////////////////////////////////////////////////// Устанавливаем целевую доску
	solution.GoalBoard = new board(InitialDesk, X_width, Y_width);
	////////////////////////////////////////////////////////////////////////
#ifdef debug
	int** ppk = new int* [Y_width];
	for (int i = 0; i < Y_width; i++)
	{
		ppk[i] = new int[X_width];
	}

	//ppk[0][0] = 3;
	//ppk[0][1] = 0;                                      
	//ppk[1][0] = 1;
	//ppk[1][1] = 2;


	ppk[0][0] = 1;
	ppk[0][1] = 2;                          //Это место остается здесь для отладки 
	ppk[0][2] = 3;
	ppk[1][0] = 4;
	ppk[1][1] = 0;
	ppk[1][2] = 5;
	ppk[2][0] = 7;
	ppk[2][1] = 8;
	ppk[2][2] = 6;

	//ppk[0][0] = 1;
	//ppk[0][1] = 4;
	//ppk[1][0] = 3;
	//ppk[1][1] = 2;
	//ppk[2][0] = 5;
	//ppk[2][1] = 0;

	board* Initial = new board(ppk, X_width, Y_width);
#else
	////////////////////////////////////////////////////////////////////////
	board* Initial = new board(InitialDesk, X_width, Y_width);
	board::create_random(*Initial);
#endif
	////////////////////////////////////////////////// Записываем в открытый список случайную доску, полученную из целевой
	if (Initial->is_solvable())
	{
		solution.Openlist->AddToHead(*Initial); // Установка начальной доски в открытом списке
		bool IsSolution = false; // Флаг окончания поиска
		board* OpenP = &solution.Openlist->Head.pNext->m_data; //Указатель на текущую доску
		board* PLeft = nullptr; // Указатели на соседнии доски
		board* PRight = nullptr;
		board* PDown = nullptr;
		board* PUp = nullptr;
		int moves = 0; // Счетчик проделанных шагов

		std::cout<< "Целевая доска: \n" << *solution.GoalBoard << "\n";

		if (*OpenP == *solution.GoalBoard)
		{
			std::cout << "Solution found!" << "\n";
			solution.Waylist->AddToTail(*OpenP);
			IsSolution = true;
			return *solution.Waylist;
		}
		else
		{
		do
		{
			moves++;
			std::cout << moves << "\n"; // Счетчик и доска
			std::cout << *OpenP << "\n";

			PLeft = nullptr;
			PRight = nullptr;
			PDown = nullptr;
			PUp = nullptr;

			if (OpenP->zero_y == OpenP->size_y-1) // Нижняя грань
			{
				if (OpenP->zero_x == OpenP->size_x-1) // Правый нижний угол
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);

				}
				else if(OpenP->zero_x == 0) // Левый нижний угол
				{
					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);

				}
				else // Нижняя грань доски
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);

				}
			}
			else if (OpenP->zero_y == 0) // Верхняя грань
			{
				if (OpenP->zero_x == OpenP->size_x - 1) // Правый верхний угол
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

				}
				else if (OpenP->zero_x == 0) // Левый верхний угол
				{
					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

				}
				else // Верхняя грань
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

				}
			}
			else // Левая и правая грани + свободные положения
			{
				if (OpenP->zero_x == OpenP->size_x - 1) // Правая грань
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);

				}
				else if (OpenP->zero_x ==  0) // Левая грань
				{
					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);

				}
				else // Свободное положение
				{
					PLeft = new board(*OpenP);
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x] = PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
					PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
					PLeft->zero_x = PLeft->zero_x - 1;
					PLeft->zero_y = PLeft->zero_y;
					PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

					PRight = new board(*OpenP);
					PRight->board_field[PRight->zero_y][PRight->zero_x] = PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
					PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
					PRight->zero_x = PRight->zero_x + 1;
					PRight->zero_y = PRight->zero_y;
					PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

					PDown = new board(*OpenP);
					PDown->board_field[PDown->zero_y][PDown->zero_x] = PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
					PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
					PDown->zero_x = PDown->zero_x;
					PDown->zero_y = PDown->zero_y + 1;
					PDown->manhatten = PDown->manhattan(*solution.GoalBoard);

					PUp = new board(*OpenP);
					PUp->board_field[PUp->zero_y][PUp->zero_x] = PUp->board_field[PUp->zero_y - 1][PUp->zero_x];
					PUp->board_field[PUp->zero_y - 1][PUp->zero_x] = 0;
					PUp->zero_x = PUp->zero_x;
					PUp->zero_y = PUp->zero_y - 1;
					PUp->manhatten = PUp->manhattan(*solution.GoalBoard);
				}
			}

			//////////////////////////////////////////////////////////////////////////////////
			solution.Closedlist->AddToHead(*OpenP); // После нахождения досок-соседей - выносим начальную точку в закрытый список
			solution.Openlist->RemoveOne(*OpenP);

			// Для каждой найденной точки обозначается ее родительская точка
			if (PRight != nullptr)
			{
				PRight->parent = &solution.Closedlist->Head.pNext->m_data;
				PRight->depth = PRight->parent->depth + 1;
				std::cout << *PRight << "\n";
			}
			if (PLeft != nullptr)
			{
				PLeft->parent = &solution.Closedlist->Head.pNext->m_data;
				PLeft->depth = PLeft->parent->depth + 1;
				std::cout << *PLeft << "\n";
			}
			if (PUp != nullptr)
			{
				PUp->parent = &solution.Closedlist->Head.pNext->m_data;
				PUp->depth = PUp->parent->depth + 1;
				std::cout << *PUp << "\n";
			}
			if (PDown != nullptr)
			{
				PDown->parent = &solution.Closedlist->Head.pNext->m_data;
				PDown->depth = PDown->parent->depth + 1;
				std::cout << *PDown << "\n";
			}
			////////////////////////////////////////////////////////////////////////////////////

			Node* pp = solution.Openlist->Head.pNext; // Вспомогательный указатель для прохода по списку 
			while (pp != &solution.Openlist->Tail) // Проверка пройденных точек (из какой точки выгоднее прийти в эту?)
			{
				if (pp->m_data == *PLeft)
				{
					if ((pp->m_data.depth) > (PLeft->depth)) 
					{
						pp->m_data.depth = PLeft->depth;
						pp->m_data.parent = PLeft->parent;
					}
					PLeft = nullptr;
				}
				if (pp->m_data == *PRight)
				{
					if ((pp->m_data.depth) > (PRight->depth))
					{
						pp->m_data.depth = PRight->depth;
						pp->m_data.parent = PRight->parent;
					}
					PRight = nullptr;
				}
				if (pp->m_data == *PDown)
				{
					if ((pp->m_data.depth) > (PDown->depth))
					{
						pp->m_data.depth = PDown->depth;
						pp->m_data.parent = PDown->parent;
					}
					PDown = nullptr;
				}
				if (pp->m_data == *PUp)
				{
					if ((pp->m_data.depth) > (PUp->depth))
					{
						pp->m_data.depth = PUp->depth;
						pp->m_data.parent = PUp->parent;
					}
					PUp = nullptr;
				}
				pp = pp->pNext;
			}

			std::cout << "//////////////////////////////////////////////////////////////////" << "\n";

			Node* ppc = solution.Closedlist->Head.pNext; // Вторая проверка - на наличие точек в закрытом списке 
			while (ppc != &solution.Closedlist->Tail)
			{
				if (ppc->m_data == *PLeft)
				{
					PLeft = nullptr;
				}
				if (ppc->m_data == *PRight)
				{
					PRight = nullptr;
				}
				if (ppc->m_data == *PDown)
				{
					PDown = nullptr;
				}
				if (ppc->m_data == *PUp)
				{
					PUp = nullptr;
				}
				ppc = ppc->pNext;
			}

			/////////////////////////////////////////////// Далее найденные и отобранные точки вносятся в открытый список
			if (PLeft)
			{
				solution.Openlist->AddToTail(*PLeft);
			}
			if (PRight)
			{
				solution.Openlist->AddToTail(*PRight);
			}
			if (PUp)
			{
				solution.Openlist->AddToTail(*PUp);
			}
			if (PDown)
			{
				solution.Openlist->AddToTail(*PDown);
			}
			///////////////////////////////////////////// После занесения точек в открытый список требуется выбрать ту, у которой в данный момент наилучшая эвристика

			pp = solution.Openlist->Head.pNext;
			Node* BestBoard = solution.Openlist->Head.pNext; 

			while (pp != &solution.Openlist->Tail) 
			{
				if ((BestBoard->m_data.manhatten + BestBoard->m_data.depth) > (pp->m_data.manhatten + pp->m_data.depth))
				{
					BestBoard = pp;
				}

				if (BestBoard->m_data == *solution.GoalBoard) // Отдельная проверка на равенство искомой доске
				{
					std::cout << "Solution found!" << "\n";
					board* ppend = &pp->m_data;
					do
					{
						solution.Waylist->AddToTail(*ppend);
						ppend = ppend->parent;
					} while (ppend != nullptr);
					IsSolution = true;
					return *solution.Waylist;         // Если путь найден, то получаем его в виде списка досок
				}
				pp = pp->pNext;
			}

			if (solution.Openlist->m_size == 0) // На случай, если ходов больше нету
			{
				std::cout << "There is no more moves!" << "\n";
				return *solution.Waylist;
			}

			OpenP = &BestBoard->m_data;

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

void Solver::PrintSolution(const Solution* sol) const
{
	sol->moves();
	Node* pp = sol->Tail.pPrev;
	while (pp->pPrev)
	{
		std::cout << pp->m_data << "\n";
		pp = pp->pPrev;
	}
}