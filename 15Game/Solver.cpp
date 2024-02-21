#include "Solver.h"

// #define debug

// Constructors

Solver::Solver()
{
    GoalBoard = nullptr;
    Openlist = new Solution;
    Closedlist = new Solution;
    Waylist = new Solution;
}

// Destructor

Solver::~Solver()
{
    while (Openlist->Head.pNext != &Openlist->Tail)
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

// Methods

Solution Solver::solve(int **InitialDesk, const int X_width, const int Y_width, Solver solution)
{
    ////////////////////////////////////////////////// Set goal board
    solution.GoalBoard = new board(InitialDesk, X_width, Y_width);
    ////////////////////////////////////////////////////////////////////////
#ifdef debug
    int **ppk = new int *[Y_width];
    for (int i = 0; i < Y_width; i++)
    {
        ppk[i] = new int[X_width];
    }

    // ppk[0][0] = 3;
    // ppk[0][1] = 0;
    // ppk[1][0] = 1;
    // ppk[1][1] = 2;

    ppk[0][0] = 1;
    ppk[0][1] = 2; // this is for debugging
    ppk[0][2] = 3;
    ppk[1][0] = 4;
    ppk[1][1] = 0;
    ppk[1][2] = 5;
    ppk[2][0] = 7;
    ppk[2][1] = 8;
    ppk[2][2] = 6;

    // ppk[0][0] = 1;
    // ppk[0][1] = 4;
    // ppk[1][0] = 3;
    // ppk[1][1] = 2;
    // ppk[2][0] = 5;
    // ppk[2][1] = 0;

    board *Initial = new board(ppk, X_width, Y_width);
#else
    ////////////////////////////////////////////////////////////////////////
    board *Initial = new board(InitialDesk, X_width, Y_width);
    board::create_random(*Initial);
#endif
    ////////////////////////////////////////////////// Add random board to open list as a start position
    if (Initial->is_solvable())
    {
        solution.Openlist->AddToHead(*Initial);
        bool IsSolution = false;                               // search over flag
        board *OpenP = &solution.Openlist->Head.pNext->m_data; // current board pointer
        board *PLeft = nullptr;                                // neighboring boards pointers
        board *PRight = nullptr;
        board *PDown = nullptr;
        board *PUp = nullptr;
        int moves = 0; // moves counter

        std::cout << "Goal board: \n" << *solution.GoalBoard << "\n";

        if (*OpenP == *solution.GoalBoard)
        {
            std::cout << "Solution found!"
                      << "\n";
            solution.Waylist->AddToTail(*OpenP);
            IsSolution = true;
            return *solution.Waylist;
        }
        else
        {
            do
            {
                moves++;
                std::cout << moves << "\n"; // cout current moves and board
                std::cout << *OpenP << "\n";

                PLeft = nullptr;
                PRight = nullptr;
                PDown = nullptr;
                PUp = nullptr;

                if (OpenP->zero_y == OpenP->size_y - 1) // lower edge
                {
                    if (OpenP->zero_x == OpenP->size_x - 1) // right lower corner
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
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
                    else if (OpenP->zero_x == 0) // left lower corner
                    {
                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
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
                    else // lower midle
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
                        PLeft->zero_x = PLeft->zero_x - 1;
                        PLeft->zero_y = PLeft->zero_y;
                        PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
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
                else if (OpenP->zero_y == 0) // upper edge
                {
                    if (OpenP->zero_x == OpenP->size_x - 1) // right upper corner
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
                        PLeft->zero_x = PLeft->zero_x - 1;
                        PLeft->zero_y = PLeft->zero_y;
                        PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
                        PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
                        PDown->zero_x = PDown->zero_x;
                        PDown->zero_y = PDown->zero_y + 1;
                        PDown->manhatten = PDown->manhattan(*solution.GoalBoard);
                    }
                    else if (OpenP->zero_x == 0) // left upper corner
                    {
                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
                        PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
                        PRight->zero_x = PRight->zero_x + 1;
                        PRight->zero_y = PRight->zero_y;
                        PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
                        PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
                        PDown->zero_x = PDown->zero_x;
                        PDown->zero_y = PDown->zero_y + 1;
                        PDown->manhatten = PDown->manhattan(*solution.GoalBoard);
                    }
                    else // upper midle
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
                        PLeft->zero_x = PLeft->zero_x - 1;
                        PLeft->zero_y = PLeft->zero_y;
                        PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
                        PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
                        PRight->zero_x = PRight->zero_x + 1;
                        PRight->zero_y = PRight->zero_y;
                        PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
                        PDown->board_field[PDown->zero_y + 1][PDown->zero_x] = 0;
                        PDown->zero_x = PDown->zero_x;
                        PDown->zero_y = PDown->zero_y + 1;
                        PDown->manhatten = PDown->manhattan(*solution.GoalBoard);
                    }
                }
                else // left edge + right edge + free position
                {
                    if (OpenP->zero_x == OpenP->size_x - 1) // right edge
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
                        PLeft->zero_x = PLeft->zero_x - 1;
                        PLeft->zero_y = PLeft->zero_y;
                        PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
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
                    else if (OpenP->zero_x == 0) // left edge
                    {
                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
                        PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
                        PRight->zero_x = PRight->zero_x + 1;
                        PRight->zero_y = PRight->zero_y;
                        PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
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
                    else // free position
                    {
                        PLeft = new board(*OpenP);
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x] =
                            PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1];
                        PLeft->board_field[PLeft->zero_y][PLeft->zero_x - 1] = 0;
                        PLeft->zero_x = PLeft->zero_x - 1;
                        PLeft->zero_y = PLeft->zero_y;
                        PLeft->manhatten = PLeft->manhattan(*solution.GoalBoard);

                        PRight = new board(*OpenP);
                        PRight->board_field[PRight->zero_y][PRight->zero_x] =
                            PRight->board_field[PRight->zero_y][PRight->zero_x + 1];
                        PRight->board_field[PRight->zero_y][PRight->zero_x + 1] = 0;
                        PRight->zero_x = PRight->zero_x + 1;
                        PRight->zero_y = PRight->zero_y;
                        PRight->manhatten = PRight->manhattan(*solution.GoalBoard);

                        PDown = new board(*OpenP);
                        PDown->board_field[PDown->zero_y][PDown->zero_x] =
                            PDown->board_field[PDown->zero_y + 1][PDown->zero_x];
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
                solution.Closedlist->AddToHead(
                    *OpenP); // After finding neighboring descs - put the start position in closed list
                solution.Openlist->RemoveOne(*OpenP);

                // setting parrent poin for each point found
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

                Node *pp = solution.Openlist->Head.pNext; // supportive pointer for search thrue list
                while (pp != &solution.Openlist->Tail)    // Points checking (Which point is closest?)
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

                std::cout << "//////////////////////////////////////////////////////////////////"
                          << "\n";

                Node *ppc = solution.Closedlist->Head.pNext; // Checking for similar points in close list
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

                /////////////////////////////////////////////// Puting all points that have been found in close list
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
                ///////////////////////////////////////////// Looking for point with best heuristics

                pp = solution.Openlist->Head.pNext;
                Node *BestBoard = solution.Openlist->Head.pNext;

                while (pp != &solution.Openlist->Tail)
                {
                    if ((BestBoard->m_data.manhatten + BestBoard->m_data.depth) >
                        (pp->m_data.manhatten + pp->m_data.depth))
                    {
                        BestBoard = pp;
                    }

                    if (BestBoard->m_data == *solution.GoalBoard) // Checking for equality to goal board
                    {
                        std::cout << "Solution found!"
                                  << "\n";
                        board *ppend = &pp->m_data;
                        do
                        {
                            solution.Waylist->AddToTail(*ppend);
                            ppend = ppend->parent;
                        } while (ppend != nullptr);
                        IsSolution = true;
                        return *solution.Waylist; // If last board is goal - making way list
                    }
                    pp = pp->pNext;
                }

                if (solution.Openlist->m_size == 0) // If there is no more moves - wrong solveble checking
                {
                    std::cout << "There is no more moves!"
                              << "\n";
                    return *solution.Waylist;
                }

                OpenP = &BestBoard->m_data;

            } while (!IsSolution);
        }
    }
    else
    {
        std::cout << *Initial << "\n";
        std::cout << "There is no solution!"
                  << "\n";
        return *solution.Waylist;
    }
}

void Solver::PrintSolution(const Solution *sol) const
{
    sol->moves();
    Node *pp = sol->Tail.pPrev;
    while (pp->pPrev)
    {
        std::cout << pp->m_data << "\n";
        pp = pp->pPrev;
    }
}
