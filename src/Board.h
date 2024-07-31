#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Direction.h"
#include "Point.h"
#include <iostream>
#include <cassert>

class Board
{
public:
    Board();

    static bool isValidPoint(const Point& pt);
    Point findEmptyTile() const;
    void swapTiles(Point pt1, Point pt2);
    bool moveTile(Direction dir);
    static void printEmptyLines(int count);
    void randomize();
    friend std::ostream& operator<<(std::ostream& out, const Board& board);
    friend bool operator==(const Board& board1, const Board& board2);
    bool playerWon() const;

    // Provide a public accessor for SIZE
    static int getSize() { return SIZE; }

private:
    static constexpr int SIZE { 4 };
    Tile m_grid[SIZE][SIZE] {};
};

#endif // BOARD_H
