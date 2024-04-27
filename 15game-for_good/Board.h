#pragma once

#pragma once
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class board
{
    std::vector<int> board_field; // Field array
    int size_x;                   // X width
    int size_y;                   // Y width
    int zero_x;                   // Coordinates of zero by x
    int zero_y;                   // Coordinates of zero by y
    board *parent;                // Pointer to parent
    int depth;                    // Search depth
    int manhatten;                // Manhatten distance

  public:
    board();                                     // Default constructor
    board(std::vector<int> board, int x, int y); // Constructor with vector
    ~board();                                    // Destructor
    board(const board &brd);                     // Copy constructor

    static void create_random(board &brd);  // Random board generator
    bool is_solvable() const;               // Solution check
    int width() const;                      // return width
    int height() const;                     // return height
    int &zerox();                           // return column index with zero
    int &zeroy();                           // return row index with zero
    int &getXY(int x, int y);               // return value by coordinates
    int &getManh();                         // return manhattan value
    std::vector<int> &getBoard();           // return link to board
    board **getParent();                    // return pointer to parent
    int &getDepth();                        // return move number
    int manhattan(const board &goal) const; // Find manhatten distance
    bool operator==(const board &brd) const;
    bool operator!=(const board &brd) const;

  private:
    std::string to_string(const board &brd) const; // Convert board to string
    int size() const;                              // Size of the board
    int inversions() const;                        // number of inversions
    bool is_goal(const board &goal) const;         // is current board == goal board?
    board &operator=(const board &brd);

    friend std::ostream &operator<<(std::ostream &os, const board &brd);
};
