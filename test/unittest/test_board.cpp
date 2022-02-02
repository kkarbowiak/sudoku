#include "board.h"

#include "doctest.h"


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
