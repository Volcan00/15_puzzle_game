#include "Board.h"
#include <algorithm>
#include <iostream>

namespace {
    constexpr int g_consoleLines { 25 };
}

Board::Board()
{
    int defaultValue = 1;

    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            if(i == SIZE - 1 && j == SIZE - 1)
            {
                m_grid[i][j].setNum(0);
            }
            else
            {
                m_grid[i][j].setNum(defaultValue++);
            }
        }
    }
}

bool Board::isValidPoint(const Point& pt)
{
    return (pt.x >= 0 && pt.x < SIZE) && (pt.y >= 0 && pt.y < SIZE);
}

Point Board::findEmptyTile() const
{
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            if(m_grid[i][j].isEmpty())
                return { j, i };

    assert(0 && "There is no empty tile in the board!!!");
    return { -1, -1 };  // Make sure the point is valid or handled if it's not found
}

void Board::swapTiles(Point pt1, Point pt2)
{
    std::swap(m_grid[pt1.y][pt1.x], m_grid[pt2.y][pt2.x]);
}

bool Board::moveTile(Direction dir)
{
    Point emptyTile{ findEmptyTile() };
    Point adj{ emptyTile.getAdjacentPoint(-dir) };

    if(!isValidPoint(adj))
        return false;

    swapTiles(emptyTile, adj);
    return true;
}

void Board::printEmptyLines(int count)
{
    for(int i = 0; i < count; ++i)
    {
        std::cout << '\n';
    }
}

void Board::randomize()
{
    for (int i = 0; i < 1000; ++i)
    {
        bool success = moveTile(Direction::getRandomDirection());
        if (!success)
            --i;
    }
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
    Board::printEmptyLines(g_consoleLines);

    for(int i = 0; i < Board::getSize(); ++i)
    {
        for(int j = 0; j < Board::getSize(); ++j)
        {
            out << board.m_grid[i][j];
        }

        out << '\n';
    }

    return out;
}

bool operator==(const Board& board1, const Board& board2)
{
    for(int i = 0; i < Board::getSize(); ++i)
    {
        for(int j = 0; j < Board::getSize(); ++j)
        {
            if(board1.m_grid[i][j].getNum() != board2.m_grid[i][j].getNum())
            {
                return false;
            }
        }
    }

    return true;
}

bool Board::playerWon() const
{
    Board s_solved {};
    return s_solved == *this;
}
