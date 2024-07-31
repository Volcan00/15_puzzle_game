#include "UserInput.h"
#include <limits>
#include <cassert>
#include <iostream>

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'q';
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
}
