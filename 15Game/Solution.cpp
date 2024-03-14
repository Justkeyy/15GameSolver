#include "Solution.h"
#include "Board.h"

///////////////////////////////////////////////////////////////////

int Solution::Size() 
{
	return m_size;
}

void Solution::moves() 
{
	std::cout << "Minimal number of moves for solution: " << m_size << "\n";
}

Solution& Solution::operator = (const Solution& sol)
{
	m_list = sol.m_list;
	m_size = sol.m_size;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol)
{
	os << "Your list contains this elements:" << "\n";

	int count = 1;
	auto current = sol.m_list.begin();
	auto end = sol.m_list.end();

	while (current != end)
	{
		os << "board # " << count << *current << "\n";
		current++;
		count++;
	}
	os << "\n";
	return os;
}