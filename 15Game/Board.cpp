#include <iomanip>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>
#include <cmath>
#include "Board.h"

board::board(std::vector <int> arrayp, int x, int y)
{
	size_x = x;
	size_y = y;

	board_field = arrayp;

	int size = board_field.size();
	
	for (int i = 0; i < size; i++)
	{
		if (board_field.at(i) == 0)
		{
			zero_x = i % size_x;
			zero_y = i / size_x;
		}
	}

	depth = 0;
	manhatten = 0;

}

board::board(const board& brd): size_x(brd.size_x), size_y(brd.size_y), zero_x(brd.zero_x), zero_y(brd.zero_y), depth(brd.depth), manhatten(brd.manhatten), parent(brd.parent), board_field(brd.board_field)
{

}

void board::create_random(board& brd)
{
	int size = brd.size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, size-1);

	for (int i = 0; i < size; i++)
	{
		std::swap(brd.board_field.at(i), brd.board_field.at(dist(gen)));
	}

	for (int i = 0; i < size; i++)
	{
		if (brd.board_field.at(i) == 0)
		{
			brd.zero_x = i%brd.size_x;
			brd.zero_y = i/brd.size_x;
			break;
		}
	}

}

bool board::is_goal(const board& goal)
{
	int size = goal.size();

	for (int i = 0; i < size; i++)
	{
		if (board_field.at(i) != goal.board_field.at(i))
		{
			return false;
		}
	}
	return true;
}

int board::inversions()
{
	int counter = 0;
	int size = this->size();

	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (this->board_field.at(i) > this->board_field.at(j) && this->board_field.at(i) != 0 && this->board_field.at(j) != 0)
			{
				counter++;
			}
		}
	}

	return counter;
}

int board::manhattan(const board& goal)
{
	int x_my = -1;
	int y_my = -1;
	int x_goal = -1;
	int y_goal = -1;
	int M_sum = 0;

	int size = goal.size();
	bool check = false;
	int block;

	for (int i = 0; i < size; i++)
	{
		check = false;
		if (goal.board_field.at(i) != 0)
		{
			block = goal.board_field.at(i);
		}
		else
		{
			continue;
		}

		for (int j = 0; j < size; j++)
		{
			if (block == this->board_field.at(j))
			{
				x_my = j % this->size_x;
				y_my = j / this->size_x;
				x_goal = i % goal.size_x;
				y_goal = i / goal.size_y;
				M_sum = M_sum + std::fabs(x_my - x_goal) + std::fabs(y_my - y_goal);
				check = true;
			}
			if (check == true)
			{
				break;
			}
		}
	}
	
	return M_sum;
}


bool board::is_solvable()
{
	int counter = inversions();
		// check for column number parity:
		if (this->size_x % 2) // odd
		{
			if (!(counter % 2))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else //even
		{
			int rownum = std::fabs(this->zero_y - this->size_y);
			if (counter % 2 == rownum % 2)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
}


int board::size() const
{
	return (size_x * size_y);
}

std::string board::to_string(board& brd) // 1 перевода в строку - простой
{
	std::string str;
	int size = brd.size();

	for (int i = 0; i < size; i++)
	{
		str += std::to_string(brd.board_field.at(i));
		str += ", ";
		if (!(i % brd.size_x))
		{
			str += "\n";
		}
	}

	return str;
}

bool board::operator == (const board& brd) const
{
	int size = brd.size();

	if (size_x != brd.size_x || size_y != brd.size_y)
		{
			return false;
		}
	else
		{
			for (int i = 0; i < size; i++)
			{
				if (board_field.at(i) != brd.board_field.at(i))
				{
					return false;
				}
			}
		}

	return true;
}

bool board::operator != (const board& brd) const
{
	int size = brd.size();

	if (size_x != brd.size_x && size_y != brd.size_y)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (board_field.at(i) != brd.board_field.at(i))
			{
				return true;
			}
		}
	}

	return false;
}

board& board::operator = (const board& brd)
{
	size_x = brd.size_x;
	size_y = brd.size_y;
	zero_x = brd.zero_x;
	zero_y = brd.zero_y;
	board_field = brd.board_field;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const board& brd)
{
	int size = brd.size();

	os <<  "\n";
	for (int i = 0; i < size; i++)
	{
		if (!(i % brd.size_x) && i != 0)
		{
			os << "\n";
		}
		os << std::setfill('0') << std::setw(3) << brd.board_field.at(i) << " ";
		
	}
	return os;
}