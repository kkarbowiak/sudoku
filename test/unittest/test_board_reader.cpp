#include "board_reader.h"

#include "doctest.h"


TEST_CASE("Reading a board from empty values yields a board with all options in all positions")
{
    BoardReader const board_reader;
    auto const board = board_reader.read_board({});

    for (auto y = 0u; y < Board::height(); ++y)
    {
        for (auto x = 0u; x < Board::width(); ++x)
        {
            for (auto v : Board::options())
            {
                REQUIRE(board.has_option(x, y, v));
            }
        }
    }
}
