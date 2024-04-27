#include "Board.h"

board::board()
    : board_field(std::vector<int>()), size_x(0), size_y(0), zero_x(0), zero_y(0), parent(nullptr), depth(0),
      manhatten(0)
{
}

board::board(std::vector<int> arrayp, int x, int y) : size_x(x), size_y(y), board_field(arrayp), depth(0), manhatten(0)
{

    for (int i = 0; i < board_field.size(); i++)
    {
        if (board_field[i] == 0)
        {
            zero_x = i % size_x;
            zero_y = i / size_x;
        }
    }
}

board::board(const board &brd)
    : size_x(brd.size_x), size_y(brd.size_y), zero_x(brd.zero_x), zero_y(brd.zero_y), depth(brd.depth),
      manhatten(brd.manhatten), parent(brd.parent), board_field(brd.board_field)
{
}

board::~board()
{
}

void board::create_random(board &brd)
{
    int size = brd.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < size; i++)
    {
        std::swap(brd.board_field[i], brd.board_field[dist(gen)]);
    }

    for (int i = 0; i < size; i++)
    {
        if (brd.board_field[i] == 0)
        {
            brd.zero_x = i % brd.size_x;
            brd.zero_y = i / brd.size_x;
            break;
        }
    }
}

bool board::is_goal(const board &goal) const
{
    int size = goal.size();

    for (int i = 0; i < size; i++)
    {
        if (board_field[i] != goal.board_field[i])
        {
            return false;
        }
    }
    return true;
}

int board::inversions() const
{
    int counter = 0;
    int size = this->size();

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (this->board_field[i] > this->board_field[j] && this->board_field[i] != 0 && this->board_field[j] != 0)
            {
                counter++;
            }
        }
    }

    return counter;
}

int board::manhattan(const board &goal) const
{
    int x_my;
    int y_my;
    int x_goal;
    int y_goal;
    int M_sum = 0;

    int size = goal.size();
    int block;

    for (int i = 0; i < size; i++)
    {
        if (goal.board_field[i] == 0)
        {
            continue;
        }
        else
        {
            block = goal.board_field[i];
        }

        for (int j = 0; j < size; j++)
        {
            if (block == this->board_field[j])
            {
                x_my = j % this->size_x;
                y_my = j / this->size_x;
                x_goal = i % goal.size_x;
                y_goal = i / goal.size_y;
                M_sum = M_sum + std::abs(x_my - x_goal) + std::abs(y_my - y_goal);
                break;
            }
        }
    }

    return M_sum;
}

bool board::is_solvable() const
{
    int counter = inversions(); // check for column number parity:
    if (this->size_x % 2)       // odd
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
    else // even
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

std::string board::to_string(const board &brd) const // to string
{
    std::string str;
    int size = brd.size();

    for (int i = 0; i < size; i++)
    {
        str += std::to_string(brd.board_field[i]);
        str += ", ";
        if (!(i % brd.size_x))
        {
            str += "\n";
        }
    }

    return str;
}

int board::width() const
{
    return this->size_x;
}

int board::height() const
{
    return this->size_y;
}

int &board::zerox()
{
    return this->zero_x;
}

int &board::zeroy()
{
    return this->zero_y;
}

int &board::getXY(int x, int y)
{
    return this->board_field[this->size_x * y + x];
}

int &board::getManh()
{
    return this->manhatten;
}

board **board::getParent()
{
    return &this->parent;
}

int &board::getDepth()
{
    return this->depth;
}

std::vector<int> &board::getBoard()
{
    return this->board_field;
}

bool board::operator==(const board &brd) const
{
    if (size_x != brd.size_x || size_y != brd.size_y)
    {
        return false;
    }
    else
    {
        return board_field == brd.board_field;
    }
}

bool board::operator!=(const board &brd) const
{

    if (size_x != brd.size_x && size_y != brd.size_y)
    {
        return true;
    }
    else
    {
        return !(board_field == brd.board_field);
    }

    return false;
}

board &board::operator=(const board &brd)
{
    size_x = brd.size_x;
    size_y = brd.size_y;
    zero_x = brd.zero_x;
    zero_y = brd.zero_y;
    board_field = brd.board_field;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const board &brd)
{
    int size = brd.size();

    os << "\n";
    for (int i = 0; i < size; i++)
    {
        if (!(i % brd.size_x) && i != 0)
        {
            os << "\n";
        }
        os << std::setfill('0') << std::setw(3) << brd.board_field[i] << " ";
    }
    return os;
}
