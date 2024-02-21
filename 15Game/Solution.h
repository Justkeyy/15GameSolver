#pragma once
#include "Node.h"

class Solution
{
    Node Head;
    Node Tail;
    size_t m_size;
    //////////////////////////////////////////
  public:
    Solution();
    Solution(const Solution &sol);
    Solution(Solution &&sol);
    ~Solution();

    int Size() const;
    void AddToHead(const board &brd);
    void AddToTail(const board &brd);
    bool RemoveOne(const board &brd);
    void RemoveAll(const board &brd);
    void moves() const;

    Solution &operator=(const Solution &sol);
    Solution &operator=(Solution &&sol);

    friend class Node;
    friend class Solver;
    friend std::ostream &operator<<(std::ostream &os, const Solution &sol);
};
