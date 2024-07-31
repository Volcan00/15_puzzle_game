#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "Direction.h"

namespace UserInput
{
    bool isValidCommand(char ch);
    void ignoreLine();
    char getCharacter();
    char getCommandFromUser();
    Direction charToDirection(char ch);
}

#endif // USER_INPUT_H
