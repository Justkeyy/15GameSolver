#include "Solver.h"
// #define debug

Solver::Solver()
{
}

Solver::~Solver()
{
}

board Solver::debuging(const board &InitialDesk) // this is for debugging
{
    std::vector<int> debbrd;
    int X_width = InitialDesk.width();
    int Y_width = InitialDesk.height();

    debbrd.resize(X_width * Y_width);

    if (X_width * Y_width == 4)
    {
        debbrd[0] = 2;
        debbrd[1] = 0;
        debbrd[2] = 1;
        debbrd[3] = 3;
    }

    if (X_width * Y_width == 9)
    {
        debbrd[0] = 1;
        debbrd[1] = 2;
        debbrd[2] = 3;
        debbrd[3] = 4;
        debbrd[4] = 5;
        debbrd[5] = 0;
        debbrd[6] = 7;
        debbrd[7] = 8;
        debbrd[8] = 6;
    }

    if (X_width * Y_width == 6)
    {
        debbrd[0] = 0;
        debbrd[1] = 2;
        debbrd[2] = 5;
        debbrd[3] = 1;
        debbrd[4] = 3;
        debbrd[5] = 4;
    }

    if (X_width * Y_width == 16)
    {
        debbrd[0] = 1;
        debbrd[1] = 2;
        debbrd[2] = 3;
        debbrd[3] = 4;
        debbrd[4] = 5;
        debbrd[5] = 6;
        debbrd[6] = 7;
        debbrd[7] = 8;
        debbrd[8] = 9;
        debbrd[9] = 10;
        debbrd[10] = 11;
        debbrd[11] = 12;
        debbrd[12] = 15;
        debbrd[13] = 13;
        debbrd[14] = 14;
        debbrd[15] = 0;
    }

    board brd(debbrd, X_width, Y_width);
    return brd;
}

void Solver::LeftNeighbour(board &brd, const board &goal)
{
    std::swap(brd.getXY(brd.zerox(), brd.zeroy()), brd.getXY(brd.zerox() - 1, brd.zeroy()));
    brd.zerox() = brd.zerox() - 1;
    brd.getManh() = brd.manhattan(goal);
}

void Solver::RightNeighbour(board &brd, const board &goal)
{
    std::swap(brd.getXY(brd.zerox(), brd.zeroy()), brd.getXY(brd.zerox() + 1, brd.zeroy()));
    brd.zerox() = brd.zerox() + 1;
    brd.getManh() = brd.manhattan(goal);
}

void Solver::UpNeighbour(board &brd, const board &goal)
{
    std::swap(brd.getXY(brd.zerox(), brd.zeroy()), brd.getXY(brd.zerox(), brd.zeroy() - 1));
    brd.zeroy() = brd.zeroy() - 1;
    brd.getManh() = brd.manhattan(goal);
}

void Solver::DownNeighbour(board &brd, const board &goal)
{
    std::swap(brd.getXY(brd.zerox(), brd.zeroy()), brd.getXY(brd.zerox(), brd.zeroy() + 1));
    brd.zeroy() = brd.zeroy() + 1;
    brd.getManh() = brd.manhattan(goal);
}

void Solver::LowerEdge(std::vector<board *> boardsvec, const board &goal)
{
    if (boardsvec[0]->zerox() == boardsvec[0]->width() - 1) // right lower corner
    {
        LeftNeighbour(*boardsvec[1], goal);
        UpNeighbour(*boardsvec[4], goal);
        //////////////////////////////////////////////////////////
        delete boardsvec[2];
        delete boardsvec[3];
    }

    else if (boardsvec[0]->zerox() == 0) // left lower corner
    {
        RightNeighbour(*boardsvec[2], goal);
        UpNeighbour(*boardsvec[4], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[1];
        delete boardsvec[3];
    }

    else // lower midle
    {
        LeftNeighbour(*boardsvec[1], goal);
        RightNeighbour(*boardsvec[2], goal);
        UpNeighbour(*boardsvec[4], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[3];
    }
}

void Solver::UpperEdge(std::vector<board *> boardsvec, const board &goal)
{
    if (boardsvec[0]->zerox() == boardsvec[0]->width() - 1) // right upper corner
    {
        LeftNeighbour(*boardsvec[1], goal);
        DownNeighbour(*boardsvec[3], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[4];
        delete boardsvec[2];
    }

    else if (boardsvec[0]->zerox() == 0) // left upper corner
    {
        RightNeighbour(*boardsvec[2], goal);
        DownNeighbour(*boardsvec[3], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[4];
        delete boardsvec[1];
    }

    else // upper midle
    {
        LeftNeighbour(*boardsvec[1], goal);
        RightNeighbour(*boardsvec[2], goal);
        DownNeighbour(*boardsvec[3], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[4];
    }
}

void Solver::LRFPossition(std::vector<board *> boardsvec, const board &goal)
{
    if (boardsvec[0]->zerox() == boardsvec[0]->width() - 1) // right edge
    {
        LeftNeighbour(*boardsvec[1], goal);
        UpNeighbour(*boardsvec[4], goal);
        DownNeighbour(*boardsvec[3], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[2];
    }

    else if (boardsvec[0]->zerox() == 0) // left edge
    {
        RightNeighbour(*boardsvec[2], goal);
        UpNeighbour(*boardsvec[4], goal);
        DownNeighbour(*boardsvec[3], goal);
        /////////////////////////////////////////////////////////
        delete boardsvec[1];
    }

    else // free position
    {
        LeftNeighbour(*boardsvec[1], goal);
        RightNeighbour(*boardsvec[2], goal);
        UpNeighbour(*boardsvec[3], goal);
        DownNeighbour(*boardsvec[4], goal);
    }
}

void Solver::NeighbourFound(std::vector<board *> boardsvec, const board &goal)
{
    if (boardsvec[0]->zeroy() == boardsvec[0]->height() - 1) // lower edge
    {
        LowerEdge(boardsvec, goal);
    }
    else if (boardsvec[0]->zeroy() == 0) // upper edge
    {
        UpperEdge(boardsvec, goal);
    }
    else // left edge + right edge + free position
    {
        LRFPossition(boardsvec, goal);
    }
}

void Solver::SetParent(std::vector<board *> boardsvec)
{
    std::vector<board *>::iterator itr = boardsvec.begin() + 1;
    while (itr != boardsvec.end())
    {
        if ((*itr)->getBoard().size() != 0)
        {
            *(*itr)->getParent() = *(end(Closedlist) - 1);
            (*itr)->getDepth() = (*(*itr)->getParent())->getDepth() + 1;
            std::cout << **itr << "\n"; // cout all neighbours
        }
        ++itr;
    }
}

void Solver::FindSimilar(std::vector<board *> boardsvec)
{
    std::vector<board *>::iterator itrcl = begin(Closedlist);

    while (itrcl != end(Closedlist))
    {
        std::vector<board *>::iterator itrvec = boardsvec.begin() + 1;
        while (itrvec != boardsvec.end())
        {
            if ((*itrvec)->getBoard().size() != 0 && **itrvec == **itrcl)
            {
                delete *itrvec;
            }
            ++itrvec;
        }
        ++itrcl;
    }
}

void Solver::PutToOpen(std::vector<board *> boardsvec)
{

    std::vector<board *>::iterator itr = boardsvec.begin() + 1;

    while (itr != boardsvec.end())
    {
        if ((*itr)->getBoard().size() != 0)
        {
            push_back(Openlist, *itr);
        }
        ++itr;
    }
}

board *Solver::FindBest(const board &InitialDesk)
{
    std::vector<board *>::iterator itr = begin(Openlist) + 1;
    board *BestBoard = *begin(Openlist);

    while (itr != end(Openlist))
    {
        if ((BestBoard->getManh() + BestBoard->getDepth()) > ((*itr)->getManh() + (*itr)->getDepth()))
        {
            BestBoard = *itr;
        }

        if (*BestBoard == InitialDesk)
        {
            std::cout << "Solution found!" << "\n";
            std::cout << "Size of open list: " << "\n";

            std::cout << getList(Openlist).size() << "\n";

            board *ppend = *itr;
            do
            {
                push_back(Waylist, new board(*ppend));
                ppend = *ppend->getParent();
            } while (ppend != nullptr);

            moves(Waylist);

            return BestBoard;
        }

        ++itr;
    }

    return BestBoard;
}

Solution Solver::solve(const board &InitialDesk)
{
#ifdef debug // for debuging
    board *Initial = new board(debuging(InitialDesk));
    Initial->getManh() = Initial->manhattan(InitialDesk);
#else
    ////////////////////////////////////////////////////////////////////////
    board *Initial = new board(InitialDesk);
    board::create_random(*Initial);
    Initial->getManh() = Initial->manhattan(InitialDesk);
#endif
    Solver solution;
    if (Initial->is_solvable())
    {
        solution.push_back(solution.Openlist, Initial);

        std::vector<board *> boardsvec = {*(solution.getList(solution.Openlist).end() - 1), nullptr, nullptr, nullptr,
                                          nullptr}; // vector of boards
        // [0] - best board (OpenP); [1] - Left board; [2] - Right board; [3] - Down board; [4] - Up board

        int moves = 0; // moves counter

        std::cout << " \n Goal board: \n" << InitialDesk << "\n";

        if (*boardsvec[0] == InitialDesk) // check if start board is already solved
        {
            std::cout << "Solution found!" << "\n";
            solution.push_back(solution.Waylist, boardsvec[0]);
            return solution.Waylist;
        }

        while (*boardsvec[0] != InitialDesk)
        {
            moves++;
            std::cout << "\n" << moves << "\n"; // cout current moves and board
            std::cout << *boardsvec[0] << "\n";
            for (std::vector<board *>::iterator itr = boardsvec.begin() + 1; itr != boardsvec.end(); itr++)
            {
                *itr = new board(*boardsvec[0]);
            }

            solution.NeighbourFound(boardsvec, InitialDesk);

            solution.push_back(solution.Closedlist, boardsvec[0]);

            solution.getList(solution.Openlist)
                .erase(std::find(solution.begin(solution.Openlist), solution.end(solution.Openlist), boardsvec[0]));

            solution.SetParent(boardsvec); // setting parrent poin for each point found

            std::cout << "\n"
                      << "//////////////////////////////////////////////////////////////////" << "\n";

            solution.FindSimilar(boardsvec); // Checking for similar points in closed list

            solution.PutToOpen(boardsvec); // Puting all points that have been found in open list

            boardsvec[0] = solution.FindBest(InitialDesk); // Looking for point with best heuristics
        }

        return solution.Waylist;
    }
    else
    {
        std::cout << *Initial << "\n";
        std::cout << "There is no solution!" << "\n";

        delete Initial;

        return solution.Waylist;
    }
}
