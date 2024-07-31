#ifndef TILE_H
#define TILE_H

#include "Point.h"

class Tile
{
public:
    Tile() = default;
    explicit Tile(int num);

    int getNum() const;
    void setNum(int value);
    bool isEmpty() const;

    friend std::ostream& operator<<(std::ostream& out, const Tile& tile);

private:
    int m_tileNum {};
    Point m_point {};
};

#endif // TILE_H
