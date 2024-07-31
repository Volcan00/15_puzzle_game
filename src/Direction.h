#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>
#include "Random.h"

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    explicit Direction(Type type);

    Type getType() const;
    Direction operator-() const;

    friend std::ostream& operator<<(std::ostream& out, const Direction& dir);

    static Direction getRandomDirection();

private:
    Type m_type {};
};

#endif // DIRECTION_H
