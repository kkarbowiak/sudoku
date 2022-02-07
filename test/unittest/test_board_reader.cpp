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

TEST_CASE("Reading a board from all zeros yields a board with all options in all positions")
{
    BoardReader const board_reader;
    auto const board = board_reader.read_board({"000000000", "000000000", "000000000", "000000000", "000000000", "000000000", "000000000", "000000000", "000000000"});

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

TEST_CASE("Reading a board from non-zero values yields a board with the positions fixed")
{
    BoardReader const board_reader;
    auto const board = board_reader.read_board({"123456789"});

    REQUIRE(board.is_fixed_at(0u, 0u));
    REQUIRE(board.is_fixed_at(1u, 0u));
    REQUIRE(board.is_fixed_at(2u, 0u));
    REQUIRE(board.is_fixed_at(3u, 0u));
    REQUIRE(board.is_fixed_at(4u, 0u));
    REQUIRE(board.is_fixed_at(5u, 0u));
    REQUIRE(board.is_fixed_at(6u, 0u));
    REQUIRE(board.is_fixed_at(7u, 0u));
    REQUIRE(board.is_fixed_at(8u, 0u));
}

TEST_CASE("Reading a board from non-zero values yields a board with the values")
{
    BoardReader const board_reader;
    auto const board = board_reader.read_board({"123456789"});

    REQUIRE(board.has_option(0u, 0u, 1u));
    REQUIRE(board.has_option(1u, 0u, 2u));
    REQUIRE(board.has_option(2u, 0u, 3u));
    REQUIRE(board.has_option(3u, 0u, 4u));
    REQUIRE(board.has_option(4u, 0u, 5u));
    REQUIRE(board.has_option(5u, 0u, 6u));
    REQUIRE(board.has_option(6u, 0u, 7u));
    REQUIRE(board.has_option(7u, 0u, 8u));
    REQUIRE(board.has_option(8u, 0u, 9u));
}
