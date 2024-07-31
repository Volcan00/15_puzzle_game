#include <gtest/gtest.h>
#include "../src/Random.h"
#include "../src/Direction.h"
#include "../src/Point.h"
#include "../src/Tile.h"
#include "../src/Board.h"
#include "../src/UserInput.h"

TEST(DirectionTest, GetType)
{
    Direction up    { Direction::Direction::up };
    Direction down  { Direction::down };
    Direction left  { Direction::left };
    Direction right { Direction::right };

    EXPECT_EQ(up.getType(), Direction::up);
    EXPECT_EQ(down.getType(), Direction::down);
    EXPECT_EQ(left.getType(), Direction::left);
    EXPECT_EQ(right.getType(), Direction::right);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}