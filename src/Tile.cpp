#include "Tile.h"
#include <iostream>

Tile::Tile(int num) : m_tileNum{ num } {}

int Tile::getNum() const
{
    return m_tileNum;
}

void Tile::setNum(int value)
{
    m_tileNum = value;
}

bool Tile::isEmpty() const
{
    return m_tileNum == 0;
}

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    if(tile.m_tileNum == 0)
        out << "    ";
    else if(tile.m_tileNum > 9)
        out << " " << tile.m_tileNum << " ";
    else
        out << "  " << tile.m_tileNum << " ";

    return out;
}
