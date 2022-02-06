#include "board.h"

#include "doctest.h"


TEST_CASE("Board has width of 9")
{
    REQUIRE(Board::width() == 9);
}

TEST_CASE("Board has a height of 9")
{
    REQUIRE(Board::height() == 9);
}

TEST_CASE("Board has options of 1..9")
{
    REQUIRE(Board::options() == std::array{1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u});
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

TEST_CASE("Board initially is not fixed anywhere")
{
    Board const board;

    for (auto y = 0u; y < Board::height(); ++y)
    {
        for (auto x = 0u; x < Board::width(); ++x)
        {
            REQUIRE(!board.is_fixed_at(x, y));
        }
    }
}

TEST_CASE("Fixing a value at x,y makes the position fixed")
{
    for (auto y = 0u; y < Board::height(); ++y)
    {
        for (auto x = 0u; x < Board::width(); ++x)
        {
            Board board;

            board.fix_option(x, y, Board::options().front());

            REQUIRE(board.is_fixed_at(x, y));
        }
    }
}

TEST_CASE("Fixing a value at x,y removes it from x-column and y-row")
{
    for (auto y = 0u; y < Board::height(); ++y)
    {
        for (auto x = 0u; x < Board::width(); ++x)
        {
            Board board;
            auto const v = Board::options().front();

            board.fix_option(x, y, v);

            for (auto yy = 0u; yy < Board::height(); ++yy)
            {
                if (yy != y)
                {
                    REQUIRE(!board.has_option(x, yy, v));
                }
            }

            for (auto xx = 0u; xx < Board::width(); ++xx)
            {
                if (xx != x)
                {
                    REQUIRE(!board.has_option(xx, y, v));
                }
            }
        }
    }
}

auto round_coord(unsigned int c)
{
    return 3u * (c / 3u);
}

TEST_CASE("Fixing a value at x,y removes it from corresponding 3x3 square")
{
    for (auto y = 0u; y < Board::height(); ++y)
    {
        for (auto x = 0u; x < Board::width(); ++x)
        {
            Board board;
            auto const v = Board::options().front();

            board.fix_option(x, y, v);

            auto const y_start = round_coord(y);
            auto const x_start = round_coord(x);
            for (auto yy = y_start; yy < y_start + 3u; ++yy)
            {
                for (auto xx = x_start; xx < x_start + 3u; ++xx)
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
