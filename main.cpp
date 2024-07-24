#include <iostream>
#include <limits>
#include<cassert>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines { 25 };

class Tile
{
public:
    Tile() = default; // Default constructor

    //Constructor with a parameter to initialize the tile number 
    explicit Tile(int num)
        : m_tileNum { num }
    {

    } 

    //Getter for tile value
    int getNum() const
    {
        return m_tileNum;
    }

    //Check if tile is empty
    bool isEmpty() const
    {
        return m_tileNum == 0;
    }

    //Overloaded output operator
    friend std::ostream& operator<<(std::ostream& out, const Tile& tile)
    {
        if(tile.m_tileNum == 0) // if empty spot
            out << "    ";
        else if(tile.m_tileNum > 9) // if two digit number
            out << " " << tile.m_tileNum << " ";
        else// if one digit number
            out << "  " << tile.m_tileNum << " ";

        return out;
    }

private:
    int m_tileNum {};
};

class Board
{
public:
    //Constructor to initialize the board
    Board () = default;

    static void printEmptyLines(int count)
    {
        for(int i = 0; i < count; ++i)
        {
            std::cout << '\n';
        }
    }

    //Overloaded output operator for the board
    friend std::ostream& operator<<(std::ostream& out, Board& board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space.
        printEmptyLines(g_consoleLines);

        for(int i = 0; i < SIZE; ++i)
        {
            for(int j = 0; j < SIZE; ++j)
            {
                out << board.m_grid[i][j];
            }

            out << '\n';
        }

        return out;
    }

private:
    static constexpr int SIZE { 4 };
    Tile m_grid[SIZE][SIZE] { Tile { 1 }, Tile { 2 }, Tile { 3 }, Tile{ 4 }, 
                              Tile{ 5 }, Tile{ 6 }, Tile{ 7 }, Tile{ 8 },
                              Tile{ 9 }, Tile{ 10 }, Tile{ 11 }, Tile{ 12 },
                              Tile{ 13 }, Tile { 14 }, Tile{ 15 }, Tile{ 0 } 
                            };
};

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

    Direction (Type type)
        : m_type { type }
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up    : return Direction{ down };
        case down  : return Direction{ up };
        case left  : return Direction{ right };
        case right : return Direction{ left };
        
        default:
            assert(0 && "Uknown direction was passed!");
            return Direction { up };
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Direction& dir)
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

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type {};
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation {};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch {};
        while (!isValidCommand(ch))
            ch = getCharacter();
        
        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w' : return Direction{ Direction::up };
        case 's' : return Direction{ Direction::down };
        case 'a' : return Direction{ Direction::left };
        case 'd' : return Direction{ Direction::right };
        default:
            assert(0 && "Unsupported direction was passed!");
            return Direction{ Direction::up };
        }
    }
};

int main()
{
    Board board {};
    std::cout << board;

    for(int i = 0; i < 4; ++i)
    {
        std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    }

    std::cout << '\n';

    while (true)
    {
        char ch { UserInput::getCommandFromUser() };

        if(ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        Direction dir { UserInput::charToDirection(ch) };

        std::cout << "You entered direction: " << dir << '\n';
    }
    return 0;
}