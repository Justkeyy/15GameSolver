#pragma once
#include <forward_list>

#include "Board.h"

class Solution
{
	std::forward_list <board*> m_list;
	size_t m_size;
//////////////////////////////////////////
public:
	Solution() = default;
	Solution(const Solution& sol) = default;
	Solution(Solution&& sol) = default;
	~Solution() = default;

	int Size();
	void moves();

	Solution& operator = (const Solution& sol);

	friend std::ostream& operator<<(std::ostream& os, const Solution& sol);
	friend class Solver;
};
