#ifndef POINT_H
#define POINT_H

#include "Direction.h"

struct Point
{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2);
    friend bool operator!=(Point p1, Point p2);

    Point getAdjacentPoint(Direction dir) const;
};

#endif // POINT_H
