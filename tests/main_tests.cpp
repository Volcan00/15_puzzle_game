#include <gtest/gtest.h>
#include "../src/Random.h"
#include "../src/Direction.h"
#include "../src/Point.h"
#include "../src/Tile.h"
#include "../src/Board.h"
#include "../src/UserInput.h"

TEST(DirectionTest, GetType)
{
    Direction up    { Direction::up };
    EXPECT_EQ(up.getType(), Direction::up);

    Direction down  { Direction::down };
    EXPECT_EQ(down.getType(), Direction::down);

    Direction left  { Direction::left };
    EXPECT_EQ(left.getType(), Direction::left);

    Direction right { Direction::right };
    EXPECT_EQ(right.getType(), Direction::right);
}

TEST(DirectiopnTest, NegationOperator)
{
    Direction up    { Direction::up };
    EXPECT_EQ((-up).getType(), Direction::down);

    Direction down  { Direction::down };
    EXPECT_EQ((-down).getType(), Direction::up);

    Direction left  { Direction::left };
    EXPECT_EQ((-left).getType(), Direction::right);

    Direction right { Direction::right };
    EXPECT_EQ((-right).getType(), Direction::left );
}

TEST(DirectionTest, StreamInsertionOperator)
{
    Direction up    { Direction::up };
    Direction down  { Direction::down };
    Direction left  { Direction::left };
    Direction right { Direction::right };

    std::ostringstream out;

    out << up;
    EXPECT_EQ(out.str(), "up");

    out.str("");
    out << down;
    EXPECT_EQ(out.str(), "down");

    out.str("");
    out << left;
    EXPECT_EQ(out.str(), "left");

    out.str("");
    out << right;
    EXPECT_EQ(out.str(), "right");
}

TEST(DirectionTest, GetRandomDirection)
{
    Direction random { Direction::getRandomDirection() };
    Direction::Type type { random.getType() };
    EXPECT_TRUE(type == Direction::up || type == Direction::down || type == Direction::left || type == Direction::right);
}

TEST(PointTest, EqualityOperator)
{
    Point p1{ 0, 0 };
    Point p2{ 0, 0 };
    Point p3{ 1, 1 };

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator)
{
    Point p1{ 0, 0 };
    Point p2{ 0, 0 };
    Point p3{ 1, 1 };

    EXPECT_TRUE(p2 != p3);
    EXPECT_FALSE(p1 != p2);
}

TEST(PointTest, GetAdjacentPoint)
{
    Point p { 2, 2 };

    Point upAdj { p.getAdjacentPoint(Direction(Direction::up)) };
    EXPECT_EQ(upAdj, Point( 2, 1 ));

    Point downAdj { p.getAdjacentPoint(Direction(Direction::down)) };
    EXPECT_EQ(downAdj, Point(2, 3));

    Point leftAdj { p.getAdjacentPoint(Direction(Direction::left)) };
    EXPECT_EQ(leftAdj, Point(1, 2));

    Point rightAdj { p.getAdjacentPoint(Direction(Direction::right)) };
    EXPECT_EQ(rightAdj, Point(3, 2));
}

TEST(TileTest, ConstructorAndGetNum)
{
    Tile tile { 5 };
    EXPECT_EQ(tile.getNum(), 5);

    Tile emptyTile { 0 };
    EXPECT_EQ(emptyTile.getNum(), 0);
}

TEST(TileTest, SetNum)
{
    Tile tile { 5 };
    tile.setNum(10);
    EXPECT_EQ(tile.getNum(), 10);

    tile.setNum(0);
    EXPECT_EQ(tile.getNum(), 0);
}

TEST(TileTest, TileIsEmpty)
{
    Tile emptyTile { 0 };
    EXPECT_TRUE(emptyTile.isEmpty());

    Tile nonEmptyTile { 5 };
    EXPECT_FALSE(nonEmptyTile.isEmpty());
}

TEST(TileTest, StreamInsertOperation)
{
    Tile tile1 { 5 };
    Tile tile2 { 10 };
    Tile tile3 { 0 };

    std::ostringstream out;

    out << tile1;
    EXPECT_EQ(out.str(), "  5 ");

    out.str("");
    out << tile2;
    EXPECT_EQ(out.str(), " 10 ");

    out.str("");
    out << tile3;
    EXPECT_EQ(out.str(), "    ");
}

TEST(BoardTest, ConstructorAndInitialState)
{
    Board board;

    EXPECT_EQ(board.findEmptyTile(), Point(3, 3));
    EXPECT_TRUE(board.playerWon());
}

TEST(BoardTest, PointIsValid)
{
    Board board;
    EXPECT_TRUE(board.isValidPoint(Point(0, 0)));
    EXPECT_TRUE(board.isValidPoint(Point(3, 3)));
    EXPECT_FALSE(board.isValidPoint(Point(-1, 0)));
    EXPECT_FALSE(board.isValidPoint(Point(0, 4)));
}

TEST(BoardTest, FindEmptyTile)
{
    Board board;
    Point emptyTile { board.findEmptyTile() };
    EXPECT_EQ(emptyTile, Point(3, 3));
}

TEST(BoardTest, SwapTile)
{
    Board board;
    Point emptyTile { board.findEmptyTile() };
    Point adjTile { emptyTile.getAdjacentPoint(Direction(Direction::up)) };

    board.swapTiles(emptyTile, adjTile);

    EXPECT_EQ(board.findEmptyTile(), adjTile);
}

// Test valid tile move
TEST(BoardTest, MoveTileValidDirection) {
    Board board;
    
    EXPECT_TRUE(board.moveTile(Direction(Direction::down)));
    EXPECT_EQ(board.findEmptyTile(), Point(3, 2));

    EXPECT_FALSE(board.moveTile(Direction(Direction::left)));
}

TEST(BoardTest, PrintEmptyLines)
{
    Board board;
    
    testing::internal::CaptureStdout();
    
    int count = 5;
    board.printEmptyLines(count);
    
    std::string output = testing::internal::GetCapturedStdout();
    
    // Create the expected output
    std::string expectedOutput(count, '\n');
    
    // Check if the captured output matches the expected output
    EXPECT_EQ(output, expectedOutput);
}

TEST(BoardTest, RandomizeBoard)
{
    Board board;
    Board boardBefore { board };
    board.randomize();

    EXPECT_FALSE(board == boardBefore);
}

TEST(BoardTest, StreamInsertionOpearor)
{
    Board board;
    std::ostringstream out;
    out << board;
    EXPECT_EQ(out.str(), "  1   2   3   4 \n  5   6   7   8 \n  9  10  11  12 \n 13  14  15     \n");
}

TEST(BoardTest, EqualityOperator)
{
    Board board1;
    Board board2;
    EXPECT_TRUE(board1 == board2);

    // Modify board2
    Point emptyTile = board2.findEmptyTile();
    Point adjacentTile = emptyTile.getAdjacentPoint(Direction(Direction::up)); // Assuming SIZE is 4
    board2.swapTiles(emptyTile, adjacentTile);

    EXPECT_FALSE(board1 == board2);
}


TEST(BoardTest, PlayerWon) {
    Board board;
    EXPECT_TRUE(board.playerWon());

    board.moveTile(Direction(Direction::down));
    EXPECT_FALSE(board.playerWon());
}

TEST(UserInputTest, IsValidCommand) {
    EXPECT_TRUE(UserInput::isValidCommand('w'));
    EXPECT_TRUE(UserInput::isValidCommand('a'));
    EXPECT_TRUE(UserInput::isValidCommand('s'));
    EXPECT_TRUE(UserInput::isValidCommand('d'));
    EXPECT_TRUE(UserInput::isValidCommand('q'));
    EXPECT_FALSE(UserInput::isValidCommand('x'));
    EXPECT_FALSE(UserInput::isValidCommand('1'));
}

TEST(UserInputTest, IgnoreLine) {
    std::istringstream input("test\nanother line\n");
    std::cin.rdbuf(input.rdbuf());

    UserInput::ignoreLine();
    std::string remainingInput;
    std::getline(std::cin, remainingInput);

    EXPECT_EQ(remainingInput, "another line");
}

TEST(UserInputTest, GetCharacter) {
    std::istringstream input("c\n");
    std::cin.rdbuf(input.rdbuf());

    char result = UserInput::getCharacter();
    EXPECT_EQ(result, 'c');
}

TEST(UserInputTest, GetCommandFromUser) {
    std::istringstream input("x\nw\n");
    std::cin.rdbuf(input.rdbuf());

    char result = UserInput::getCommandFromUser();
    EXPECT_EQ(result, 'w');
}

TEST(UserInputTest, CharToDirection) {
    EXPECT_EQ(UserInput::charToDirection('w').getType(), Direction::up);
    EXPECT_EQ(UserInput::charToDirection('s').getType(), Direction::down);
    EXPECT_EQ(UserInput::charToDirection('a').getType(), Direction::left);
    EXPECT_EQ(UserInput::charToDirection('d').getType(), Direction::right);
    EXPECT_DEATH(UserInput::charToDirection('x'), "Unsupported direction was passed!");
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}