#include "Board.h"
#include "UserInput.h"
#include <iostream>

int main()
{
    Board board {};
    board.randomize();
    std::cout << board;

    std::cout << "Enter a command: ";
    while (!board.playerWon())
    {
        char ch { UserInput::getCommandFromUser() };

        if(ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            break;
        }

        Direction dir { UserInput::charToDirection(ch) };

        bool userMoved { board.moveTile(dir) };
        if(userMoved)
            std::cout << board;
    }

    std::cout << "\n\nYou won\n\n";

    return 0;
}
