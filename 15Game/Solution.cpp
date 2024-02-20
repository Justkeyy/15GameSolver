
#include "Solution.h"
#include "Board.h"

Solution::Solution() : m_size(0)
{
	Head.pNext = &Tail;
	Tail.pPrev = &Head;
}

Solution::Solution(Solution&& sol) :m_size(sol.m_size), Head(sol.Head), Tail(sol.Tail)
{
	if (sol.m_size > 0)
	{
		Head.pNext->pPrev = &Head;
		Tail.pPrev->pNext = &Tail;
		sol.Head.pNext = &sol.Tail;
		sol.Tail.pPrev = &sol.Head;
		sol.m_size = 0;
	}
	else
	{
		Head.pNext = &Tail;
		Tail.pPrev = &Head;
	}
}

Solution::Solution(const Solution& sol)
{
	Head.pNext = &Tail;
	Tail.pPrev = &Head;
	m_size = 0;
	Node* p = Tail.pPrev;
	Node* pp = sol.Head.pNext;
	while (m_size < sol.m_size)
	{
		p = new Node(p, &pp->m_data);
		pp = pp->pNext;
		m_size++;
	}
}

Solution::~Solution()
{
	while (Head.pNext != &Tail)
	{
		delete Head.pNext;
	}
}

///////////////////////////////////////////////////////////////////

int Solution::Size() const
{
	return m_size;
}

void Solution::AddToHead(const board& brd)
{
	new Node(&Head, &brd);
	m_size++;
}

void Solution::AddToTail(const board& brd)
{
	new Node(Tail.pPrev, &brd);
	m_size++;
}

bool Solution::RemoveOne(const board& brd)
{
	Node* p = Head.pNext;
	while (p != &Tail)
	{
		if (p->m_data == brd)
		{
			m_size--;
			delete p;
			return true;
		}
		p = p->pNext;
	}
	return false;
}

void Solution::RemoveAll(const board& brd)
{
	Node* p = Head.pNext;
	while (p != &Tail)
	{
		Node* n = p->pNext;
		if (p->m_data == brd)
		{
			m_size--;
			delete p;
		}
		p = n;
	}
}

void Solution::moves() const
{
	std::cout << "Minimal number of moves for solution: " << m_size << "\n";
}

Solution& Solution::operator = (const Solution& sol)
{
	if (this == &sol)
	{
		return *this;
	}
	if (!&sol)
	{
		return *this;
	}

	for (int i = sol.m_size; i < m_size; i++)
	{
		delete Head.pNext;
	}

	Node* p = Head.pNext;
	Node* pp = sol.Head.pNext;

	if (m_size < sol.m_size)
	{
		for (int i = 0; i < m_size; i++)
		{
			p->m_data = pp->m_data;
			p = p->pNext;
			pp = pp->pNext;
		}
		for (int i = m_size; i < sol.m_size; i++)
		{
			AddToTail(pp->m_data);
			pp = pp->pNext;
		}
	}
	else
	{
		for (int i = 0; i < sol.m_size; i++)
		{
			p->m_data = pp->m_data;
			p = p->pNext;
			pp = pp->pNext;
		}
	}
	m_size = sol.m_size;
	return *this;
}

Solution& Solution::operator = (Solution&& sol)
{
	if (this == &sol)
	{
		return *this;
	}
	for (int i = 0; i < m_size; i++)
	{
		delete Head.pNext;
	}

	if (sol.m_size > 0)
	{
		Head = sol.Head;
		Tail = sol.Tail;
		Head.pNext->pPrev = &Head;
		Tail.pPrev->pNext = &Tail;
		sol.Head.pNext = &sol.Tail;
		sol.Tail.pPrev = &sol.Head;
		m_size = sol.m_size;
		sol.m_size = 0;
	}
	else
	{
		Head.pNext = &Tail;
		Tail.pPrev = &Head;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol)
{
	os << "Your list contains this elements:" << "\n";

	int count = 1;
	Node* p = sol.Head.pNext;

	while (p != &sol.Tail)
	{
		os << "board # " << count << p->m_data << "\n";
		p = p->pNext;
		count++;
	}
	os << "\n";
	return os;
}