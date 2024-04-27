#pragma once
#include "Board.h"

class Solution
{
  protected:
    std::vector<board *> m_list;

  public:
    Solution();
    Solution(const Solution &sol);
    ~Solution();

  protected:
    std::vector<board *>::iterator begin();
    std::vector<board *>::iterator begin(Solution &sol);
    std::vector<board *>::iterator end();
    std::vector<board *>::iterator end(Solution &sol);
    void push_back(Solution &sol, board *brd);
    void moves() const; // minimal number of mpves to get solution
    void moves(Solution &sol) const;
    std::vector<board *> &getList(); // returns link to list
    std::vector<board *> &getList(Solution &sol);

  public:
    Solution &operator=(const Solution &sol);
    Solution &operator=(Solution &&sol);

    friend std::ostream &operator<<(std::ostream &os, const Solution &sol);
};
