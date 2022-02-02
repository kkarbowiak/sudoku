#include "board.h"

#include "doctest.h"


TEST_CASE("Board has width of 9")
{
    Board board;

    REQUIRE(board.width() == 9);
}

TEST_CASE("Board has a height of 9")
{
    Board board;

    REQUIRE(board.height() == 9);
}

TEST_CASE("Board initially contains all options in all positions")
{
    Board board;

    for (auto y = 0; y < 9; ++y)
    {
        for (auto x = 0; x < 9; ++x)
        {
            for (auto v = 1; v <= 9; ++v)
            {
                REQUIRE(board.has_option(x, y, v));
            }
        }
    }
}
