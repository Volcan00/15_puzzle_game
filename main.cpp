#include <iostream>

class Tile
{
private:
    int m_tileNum {};

public:
    Tile() = default; // default constructor

    // constructor to create a tile with a display value 
    explicit Tile(int num)
        : m_tileNum { num }
    {

    } 

    //getter for tile value
    int getNum()
    {
        return m_tileNum;
    }

    //check if tile is empty
    bool isEmpty()
    {
        return m_tileNum == 0;
    }

    //output operator overload
    friend std::ostream& operator<<(std::ostream& out, const Tile& tile)
    {
        if(tile.m_tileNum > 9) // if two digit number
            out << " " << tile.m_tileNum << " ";
        else if(tile.m_tileNum < 9) // if one digit number
            out << "  " << tile.m_tileNum << " ";
        else if(tile.m_tileNum == 0) // if empty spot
            out << "    ";

        return out;
    }
};

int main()
{
    Tile tile1 { 10 };
    Tile tile2 { 8 };
    Tile tile3 { 0 }; // the missing tile
    Tile tile4 { 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

    return 0;
}