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

    REQUIRE(board.options() == std::array{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u});
}

TEST_CASE("Board initially is not fixed")
{
    Board const board;

    REQUIRE(!board.is_fixed());
}

TEST_CASE("Board initially is valid")
{
    Board const board;

    REQUIRE(board.is_valid());
}

TEST_CASE("Board initially contains all options in all positions")
{
    Board const board;

    for (auto y = 0; y < board.height(); ++y)
    {
        for (auto x = 0; x < board.width(); ++x)
        {
            for (auto v : board.options())
            {
                REQUIRE(board.has_option(x, y, v));
            }
        }
    }
}

TEST_CASE("Board initially is not fixed anywhere")
{
    Board const board;

    for (auto y = 0; y < board.height(); ++y)
    {
        for (auto x = 0; x < board.width(); ++x)
        {
            REQUIRE(!board.is_fixed_at(x, y));
        }
    }
}

TEST_CASE("Fixing a value at x,y makes the position fixed")
{
    for (auto y = 0; y < Board::height(); ++y)
    {
        for (auto x = 0; x < Board::width(); ++x)
        {
            Board board;

            board.fix_option(x, y, Board::options().front());

            REQUIRE(board.is_fixed_at(x, y));
        }
    }
}

TEST_CASE("Fixing a value at x,y removes it from x-column and y-row")
{
    for (auto y = 0; y < Board::height(); ++y)
    {
        for (auto x = 0; x < Board::width(); ++x)
        {
            Board board;
            auto const v = Board::options().front();

            board.fix_option(x, y, v);

            for (auto yy = 0; yy < Board::height(); ++yy)
            {
                if (yy != y)
                {
                    REQUIRE(!board.has_option(x, yy, v));
                }
            }

            for (auto xx = 0; xx < Board::width(); ++xx)
            {
                if (xx != x)
                {
                    REQUIRE(!board.has_option(xx, y, v));
                }
            }
        }
    }
}

auto round_coord(int c)
{
    return 3 * (c / 3);
}

TEST_CASE("Fixing a value at x,y removes it from corresponding 3x3 square")
{
    for (auto y = 0; y < Board::height(); ++y)
    {
        for (auto x = 0; x < Board::width(); ++x)
        {
            Board board;
            auto const v = Board::options().front();

            board.fix_option(x, y, v);

            auto const y_start = round_coord(y);
            auto const x_start = round_coord(x);
            for (auto yy = y_start; yy < y_start + 3; ++yy)
            {
                for (auto xx = x_start; xx < x_start + 3; ++xx)
                {
                    if ((yy != y) || (xx != x))
                    {
                        REQUIRE(!board.has_option(xx, yy, v));
                    }
                }
            }
        }
    }
}
