#include <iomanip>
#include <cstdlib>
#include <string>
#include "Board.h"

board::board(): size_x(0), size_y (0), zero_x (0), zero_y (0), depth (0), manhatten(0), board_field(nullptr), parent(nullptr)
{
	
}

board::board(int** arrayp, int x, int y)
{
	size_x = x;
	size_y = y;

	board_field = new int* [size_y]; 
	for (int i = 0; i < size_y; i++)
	{
		board_field[i] = new int[size_x];
	}

	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			board_field[i][j] = arrayp[i][j];
			if (board_field[i][j] == 0)
			{
				zero_x = j;
				zero_y = i;
			}
		}
	}

	depth = 0;
	manhatten = 0;

	arrayp = nullptr;
}

board::board(const board& brd): size_x(brd.size_x), size_y(brd.size_y), zero_x(brd.zero_x), zero_y(brd.zero_y), depth(brd.depth), manhatten(brd.manhatten), parent(brd.parent)
{

	if (brd.board_field)
	{
		board_field = new int* [size_y];
		for (int i = 0; i < size_y; i++)
		{
			board_field[i] = new int[size_x];
		}

		for (int i = 0; i < size_y; i++)
		{
			for (int j = 0; j < size_x; j++)
			{
				board_field[i][j] = brd.board_field[i][j];
			}
		}
	}
}

board::~board()
{
	for (int i = 0; i < size_y; i++)
	{
		delete[] board_field[i];
	}
	delete[] board_field;
	board_field = nullptr;
}

void board::create_random(board& brd)
{
	for (int i = 0; i < brd.size_y; i++)
	{
		for (int j = 0; j < brd.size_x; j++)
		{
			int R1 = std::rand()% brd.size_x;
			int R2 = std::rand()% brd.size_y;
			int R3 = std::rand() % brd.size_x;
			int R4 = std::rand() % brd.size_y;
			int temp = brd.board_field[R2][R1];
			brd.board_field[R2][R1] = brd.board_field[R4][R3];
			brd.board_field[R4][R3] = temp;
		}
	}

	for (int i = 0; i < brd.size_y; i++)
	{
		for (int j = 0; j < brd.size_x; j++)
		{
			if (brd.board_field[i][j] == 0)
			{
				brd.zero_x = j;
				brd.zero_y = i;
			}
		}
	}

}

bool board::is_goal(const board& goal)
{
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			if (board_field[i][j] != goal.board_field[i][j])
			{
				return false;
			}
		}
	}
	return false;
}

int board::hamming()
{
	int counter = 0;

	std::string str = to_string(*this);

	for (std::string::size_type i = 0; i < str.size(); i++)
	{
		if (str[i] != '0' && std::isdigit(str[i]))
		{
			for (std::string::size_type j = i; j < str.size(); j++)
			{
				if (str[i] > str[j] && std::isdigit(str[j]) && str[j] != '0')
				{
					counter++;
				}
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

	for (int i = 0; i < goal.size_y; i++)
	{
		for (int j = 0; j < goal.size_x; j++)
		{
			bool check = false;
			int block;
			if (goal.board_field[i][j] != 0)
			{
				block = goal.board_field[i][j];
			}
			else
			{
				continue;
			}

			for (int ii = 0; ii < size_y; ii++)
			{
				for (int jj = 0; jj < size_x; jj++)
				{
					if (block == board_field[ii][jj])
					{
						x_my = jj;
						y_my = ii;
						x_goal = j;
						y_goal = i;
						M_sum = M_sum + sqrt((x_my - x_goal) * (x_my - x_goal)) + sqrt((y_my - y_goal) * (y_my - y_goal));
						check = true;
					}
					if (check == true)
					{
						break;
					}
				}
				if (check == true)
				{
					break;
				}
			}

		}
	}
	
	return M_sum;
}

bool board::is_solvable()
{
	int counter = hamming();

	counter = (counter + 1 + zero_y);
	if (counter%2)
	{
		if ((size_y + size_x) % 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
	
}

int board::size()
{
	return (size_x * size_y);
}

std::string board::to_string(board& brd) // 1 перевода в строку - простой
{
	std::string str;
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			str += std::to_string(brd.board_field[i][j]);
			str += ", ";
		}
		str += "\n";
	}
	return str;
}

//std::string board::to_string(board& brd) // 2 перевода в строку - змейкой с исключениями 
//{
//	std::string str;
//
//	if (size_y > 2 && size_x > 2)
//	{
//		for (int i = 0; i < size_y; i++)
//		{
//			if (i % 2 == 0)
//			{
//				for (int j = 0; j < size_x; j++)
//				{
//					str += std::to_string(brd.board_field[i][j]);
//					str += ", ";
//				}
//				str += "\n";
//			}
//			else
//			{
//				for (int j = size_x - 1; j >= 0; j--)
//				{
//					str += std::to_string(brd.board_field[i][j]);
//					str += ", ";
//				}
//				str += "\n";
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < size_y; i++)
//			{
//				for (int j = 0; j < size_x; j++)
//				{
//					str += std::to_string(brd.board_field[i][j]);
//					str += ", ";
//				}
//				str += "\n";
//			}
//	}
//	return str;
//}

bool board::operator == (const board& brd) const
{
	if(&brd != nullptr)
	{
		if (size_x != brd.size_x && size_y != brd.size_y)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size_y; i++)
			{
				for (int j = 0; j < size_x; j++)
				{
					if (board_field[i][j] != brd.board_field[i][j])
					{
						return false;
					}
				}
			}
		}

		return true;

	}
	else
	{
		return false;
	}

}

bool board::operator != (const board& brd) const
{
	if (size_x != brd.size_x && size_y != brd.size_y)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < size_y; i++)
		{
			for (int j = 0; j < size_x; j++)
			{
				if (board_field[i][j] != board_field[i][j])
				{
					return true;
				}
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
	board_field = new int* [size_y];

	for (int i = 0; i < size_y; i++)
	{
		board_field[i] = new int[size_x];
	}

	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			board_field[i][j] = brd.board_field[i][j];
		}
	}

	return *this;
}


std::ostream& operator<<(std::ostream& os, const board& brd)
{
	os <<  "\n";

	for (int i = 0; i < brd.size_y; i++)
	{
		for (int j = 0; j < brd.size_x; j++)
		{
			os << std::setfill('0') << std::setw(3) << brd.board_field[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}