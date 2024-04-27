#include "Solution.h"

Solution::Solution()
{
}

Solution::Solution(const Solution &sol)
{
    for (int i = 0; i < sol.m_list.size(); i++)
    {
        m_list.push_back(new board(*sol.m_list[i]));
    }
}

Solution::~Solution()
{
    std::vector<board *>::iterator it = m_list.begin();

    while (it != m_list.end())
    {
        delete *it;
        it = m_list.erase(it);
    }
}

void Solution::moves() const
{
    std::cout << "Minimal number of moves for solution: " << m_list.size() - 1 << "\n";
}

void Solution::moves(Solution &sol) const
{
    std::cout << "Minimal number of moves for solution: " << sol.m_list.size() - 1 << "\n";
}

std::vector<board *> &Solution::getList()
{
    return m_list;
}

std::vector<board *> &Solution::getList(Solution &sol)
{
    return sol.m_list;
}

std::vector<board *>::iterator Solution::begin()
{
    return m_list.begin();
}

std::vector<board *>::iterator Solution::begin(Solution &sol)
{
    return sol.m_list.begin();
}

std::vector<board *>::iterator Solution::end()
{
    return m_list.end();
}

std::vector<board *>::iterator Solution::end(Solution &sol)
{
    return sol.m_list.end();
}

void Solution::push_back(Solution &sol, board *brd)
{
    sol.m_list.push_back(brd);
}

Solution &Solution::operator=(const Solution &sol)
{
    if (m_list == sol.m_list)
    {
        return *this;
    }

    std::vector<board *>::iterator itr = m_list.begin();

    while (itr != m_list.end())
    {
        delete *itr;
        itr++;
    }

    m_list.resize(sol.m_list.size());
    for (int i = 0; i < sol.m_list.size(); i++)
    {
        m_list[i] = new board(*sol.m_list[i]);
    }
    m_list.shrink_to_fit();
    return *this;
}

Solution &Solution::operator=(Solution &&sol)
{
    if (m_list == sol.m_list)
    {
        return *this;
    }

    std::vector<board *>::iterator itr = m_list.begin();

    while (itr != m_list.end())
    {
        delete *itr;
        itr++;
    }

    m_list = std::move(sol.m_list);

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Solution &sol)
{
    os << "Your list contains this elements:" << "\n";

    int count = 1;
    auto current = sol.m_list.rbegin();

    while (current != sol.m_list.rend())
    {
        os << "board # " << count << ": ";
        os << **current << "\n"
           << "\n";
        current++;
        count++;
    }
    os << "\n";
    return os;
}
