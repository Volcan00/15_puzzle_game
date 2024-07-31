#include "Direction.h"
#include <cassert>

Direction::Direction(Type type) : m_type{type} {}

Direction::Type Direction::getType() const
{
    return m_type;
}

Direction Direction::operator-() const
{
    switch (m_type)
    {
    case up    : return Direction{ down };
    case down  : return Direction{ up };
    case left  : return Direction{ right };
    case right : return Direction{ left };
    default:
        assert(0 && "Unknown direction was passed!");
        return Direction { up };
    }
}

std::ostream& operator<<(std::ostream& out, const Direction& dir)
{
    switch (dir.getType())
    {
    case Direction::up    : return (out << "up");
    case Direction::down  : return (out << "down");
    case Direction::left  : return (out << "left");
    case Direction::right : return (out << "right");
    default               : return (out << "unknown direction");
    }
}

Direction Direction::getRandomDirection()
{
    Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
    return Direction{ random };
}
