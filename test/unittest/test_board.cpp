#include "board.h"

#include "doctest.h"


TEST_CASE("Board has width of 9")
{
    Board const board;

    REQUIRE(board.width() == 9);
}

TEST_CASE("Board has a height of 9")
{
    Board const board;

    REQUIRE(board.height() == 9);
}

TEST_CASE("Board has options of 1..9")
{
    Board const board;

    REQUIRE(board.options() == std::array{1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST_CASE("Board initially contains all options in all positions")
{
    Board const board;

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
