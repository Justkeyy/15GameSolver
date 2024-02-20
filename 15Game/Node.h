#pragma once
#include "Board.h"

class Node
{
	Node* pPrev;
	Node* pNext;
	board m_data;
	Node();
	Node(Node* node, const board* brd);
	~Node();

	friend class Solution;
	friend class Solver;
	friend std::ostream& operator<<(std::ostream& os, const Solution& sol);
};

