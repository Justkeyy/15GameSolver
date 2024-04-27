#pragma once
#include "Solution.h"

class Solver : public Solution
{
    Solution Openlist;
    Solution Closedlist;
    Solution Waylist;

  public:
    Solver();
    ~Solver();

    void LeftNeighbour(board &brd, const board &goal);
    void RightNeighbour(board &brd, const board &goal);
    void UpNeighbour(board &brd, const board &goal);
    void DownNeighbour(board &brd, const board &goal);

    void LowerEdge(std::vector<board *> boardsvec, const board &goal);
    void UpperEdge(std::vector<board *> boardsvec, const board &goal);
    void LRFPossition(std::vector<board *> boardsvec, const board &goal);
    void NeighbourFound(std::vector<board *> boardsvec, const board &goal);

    void SetParent(std::vector<board *> boardsvec);
    void FindSimilar(std::vector<board *> boardsvec);
    void PutToOpen(std::vector<board *> boardsvec);
    board *FindBest(const board &InitialDesk);
    static Solution solve(const board &InitialDesk);
    static board debuging(const board &InitialDesk);
};
