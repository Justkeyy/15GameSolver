#pragma once
#include <iostream>
#include <vector>

class board
{
	std::vector <int> board_field; // Field array
	int size_x = 0; // X width
	int size_y = 0; // Y width
	int zero_x = 0; // Coordinates of zero by x
	int zero_y = 0; // Coordinates of zero by y
	board* parent = nullptr; // Link to parent
	int depth = 0; // Search depth 
	int manhatten = 0; // Manhatten distance

public:
	board() = default; // Default constructor
	board(std::vector <int> board, int x, int y); // Constructor with vector
	~board() = default; // Destructor
	board(const board& brd); // Copy constructor
private:
	static void create_random(board& brd); // Random board generator
	bool is_solvable(); // Solution check 
	std::string to_string(board& brd); // Convert board to string
	int manhattan(const board& goal); // Find manhatten distance
	int size() const; // Size of the board
	int inversions(); // number of inversions
	bool is_goal(const board& goal); // is current board == goal board?
	board& operator = (const board& brd);
	bool operator == (const board& brd) const;
	bool operator != (const board& brd) const;

	friend std::ostream& operator<<(std::ostream& os, const board& brd);
	friend class Solver;
};

